#include "directinput/directinput_device.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "SetupAPI.lib")

using namespace arch;
using namespace arch::directinput;

device::device()
: m_HasInitialized(false), m_pInput(nullptr)
{
}

device::~device()
{
}

bool device::initialize(HINSTANCE hInstance)
{
	if (m_HasInitialized)
	{
		return false;
	}

	HRESULT hr;

	// DirectInputインターフェースの作成
	hr = CoCreateInstance
		(
		CLSID_DirectInput8,						// DirectInputのCLSID
		NULL,									//
		CLSCTX_ALL,								// CLSCTX(コンテキスト)
		IID_IDirectInput8,						// DirectInputのGUID
		reinterpret_cast<void**>(&m_pInput)		// インターフェイスのポインタ
		);

	if FAILED(hr)
	{
		return false;
	}

	// DirectInputの初期化
	if FAILED(m_pInput->Initialize(GetModuleHandle(NULL), DIRECTINPUT_VERSION))
	{
		m_pInput->Release();
		m_pInput = nullptr;
		return false;
	}

	m_HasInitialized = true;

	enumerate_devices();

	return true;
}

void device::finalize()
{
	if (!m_HasInitialized)
	{
		return;
	}

	clear_devices();

	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}

	m_HasInitialized = false;
}

void device::update()
{
	for (auto& state : m_MouseStates)
	{
		update_mouse(state);
	}

	for (auto& state : m_KeyboardStates)
	{
		update_keyboard(state);
	}

	for (auto& state : m_JoystickStates)
	{
		update_joystick(state);
	}
}

void device::clear_devices()
{
	for (auto& state : m_MouseStates)
	{
		state.handle->Unacquire();
		state.handle->Release();
		state.handle = nullptr;
	}
	m_MouseStates.clear();

	for (auto& state : m_KeyboardStates)
	{
		state.handle->Unacquire();
		state.handle->Release();
		state.handle = nullptr;
	}
	m_KeyboardStates.clear();

	for (auto& state : m_JoystickStates)
	{
		state.handle->Unacquire();
		state.handle->Release();
		state.handle = nullptr;
	}
	m_JoystickStates.clear();
}

void device::enumerate_devices()
{
	clear_devices();

	m_pInput->EnumDevices(DI8DEVCLASS_POINTER, enumerate_mouses_callback, this, DIEDFL_ATTACHEDONLY);		// マウスの列挙
	m_pInput->EnumDevices(DI8DEVCLASS_KEYBOARD, enumerate_keyboards_callback, this, DIEDFL_ATTACHEDONLY);	// キーボードの列挙
	m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, enumerate_joysticks_callback, this, DIEDFL_ATTACHEDONLY);	// ゲームパッドの列挙
}

void device::set_focus(HWND hwnd)
{
	for (auto& state : m_MouseStates)
	{
		state.handle->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	}

	for (auto& state : m_KeyboardStates)
	{
		state.handle->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	}

	for (auto& state : m_JoystickStates)
	{
		state.handle->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	}
}

const std::vector<mouse_state>& device::get_mouse_states() const
{
	return m_MouseStates;
}

const std::vector<keyboard_state>& device::get_keyboard_states() const
{
	return m_KeyboardStates;
}

const std::vector<joystick_state>& device::get_joystick_states() const
{
	return m_JoystickStates;
}

BOOL CALLBACK device::enumerate_mouses_callback(const DIDEVICEINSTANCE* pDeviceInstance, void* pRef)
{
	auto device = reinterpret_cast<directinput::device*>(pRef);

	mouse_state state;
	state.handle = device->create_device(pDeviceInstance->guidInstance);
	if(state.handle == nullptr)
	{
		return DIENUM_CONTINUE;
	}
	state.name = pDeviceInstance->tszProductName;
	state.move = int3::zero();

	for (auto& key : state.keys)
	{
		key.pressed = false;
		key.released = false;
		key.clicked = false;
	}

	state.handle->SetDataFormat(&c_dfDIMouse2);

	device->m_MouseStates.push_back(std::move(state));

	return DIENUM_CONTINUE;
}

BOOL CALLBACK device::enumerate_keyboards_callback(const DIDEVICEINSTANCE* pDeviceInstance, void* pRef)
{
	auto device = reinterpret_cast<directinput::device*>(pRef);

	keyboard_state state;
	state.handle = device->create_device(pDeviceInstance->guidInstance);
	if(state.handle == nullptr)
	{
		return DIENUM_CONTINUE;
	}
	state.name = pDeviceInstance->tszProductName;

	for (auto& key : state.keys)
	{
		key.pressed = false;
		key.released = false;
		key.clicked = false;
	}

	state.handle->SetDataFormat(&c_dfDIKeyboard);

	device->m_KeyboardStates.push_back(std::move(state));

	return DIENUM_CONTINUE;
}

BOOL CALLBACK device::enumerate_joysticks_callback(const DIDEVICEINSTANCE* pDeviceInstance, void* pRef)
{
	auto device = reinterpret_cast<directinput::device*>(pRef);

	joystick_state state;
	state.handle = device->create_device(pDeviceInstance->guidInstance);
	if(state.handle == nullptr)
	{
		return DIENUM_CONTINUE;
	}
	state.name = pDeviceInstance->tszProductName;

	state.handle->SetDataFormat(&c_dfDIJoystick);

	device->m_JoystickStates.push_back(std::move(state));

	return DIENUM_CONTINUE;
}


IDirectInputDevice8* device::create_device(const GUID Guid)
{
	IDirectInputDevice8* pDevice;
	if FAILED(m_pInput->CreateDevice(Guid, &pDevice, NULL))
	{
		logging::error("IDirectInputDevice8の生成に失敗しました。", "createDevice", "Device");
		return nullptr;
	}
	return pDevice;
}

void device::update_mouse(mouse_state& state)
{
	DIMOUSESTATE2 mouseState = {0};

	// マウスの入力状態を取得
	if FAILED(state.handle->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState))
	{
		// デバイスがロストしている場合はデバイスを再取得
		if FAILED(state.handle->Acquire())
		{
			// ロストしたデバイスを取得できなかった場合
		}
		else if FAILED(state.handle->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState))
		{
			// デバイスを取得できたがマウスの入力状態を再取得できなかった場合
		}
	}

	state.move.x	= static_cast<int>(mouseState.lX);
	state.move.y	= static_cast<int>(mouseState.lY);
	state.move.z	= static_cast<int>(mouseState.lZ);

	const size_t size = state.keys.size();
	for(size_t i = 0; i < size; i++)
	{
		bool down = (mouseState.rgbButtons[i] & 0x80) != 0;
		state.keys[i].clicked = state.keys[i].pressed ? false : down;
		state.keys[i].released = state.keys[i].pressed ? !down : false;
		state.keys[i].pressed = down;
	}
}

void device::update_keyboard(keyboard_state& state)
{
	std::array<BYTE, 256> keyState = {0};
	const size_t size = keyState.size();

	// キーボードの入力状態を取得
	if FAILED(state.handle->GetDeviceState(size, &keyState))
	{
		// デバイスがロストしている場合はデバイスを再取得
		if FAILED(state.handle->Acquire())
		{
			// ロストしたデバイスを取得できなかった場合
		}
		else if FAILED(state.handle->GetDeviceState(size, &keyState))
		{
			// デバイスを取得できたがキーボードの入力状態を再取得できなかった場合
		}
	}

	for (uint i = 0; i < size; i++)
	{
		bool down = (keyState[i] >> 7) != 0;
		state.keys[i].released = state.keys[i].pressed ? !down : false;
		state.keys[i].clicked = state.keys[i].pressed ? false : down;
		state.keys[i].pressed = down;
	}
}

void device::update_joystick(joystick_state& state)
{
}

std::string device::guid_to_device_name(const GUID Guid)
{
	std::string DeviceName;

	HDEVINFO hDevInfo;
	SP_INTERFACE_DEVICE_DATA Info;

	hDevInfo	= SetupDiGetClassDevs(&Guid, NULL, NULL, (DIGCF_PRESENT | DIGCF_INTERFACEDEVICE));
	Info.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);
	if (SetupDiEnumDeviceInterfaces(hDevInfo, 0, &Guid, 0, &Info))
	{
		//デバイスインターフェース詳細を取得するために必要なメモリサイズを取得する
		DWORD Size;
		SetupDiGetDeviceInterfaceDetail(hDevInfo, &Info, NULL, 0, &Size, NULL);

		PSP_INTERFACE_DEVICE_DETAIL_DATA Detail;
		Detail = (PSP_INTERFACE_DEVICE_DETAIL_DATA)malloc(Size);
		Detail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
	
		if (SetupDiGetInterfaceDeviceDetail(hDevInfo, &Info, Detail, Size, &Size, NULL))
		{
			DeviceName = Detail->DevicePath;
		}
		free(Detail);
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);

	return DeviceName;
}