#include "rawinput/rawinput_device.h"
#include <hidsdi.h>

#pragma comment(lib, "Hid.lib")

using namespace arch;
using namespace arch::rawinput;

device::device()
{
}

device::~device()
{
}

bool device::reset()
{
	m_MouseStates.clear();
	m_KeyboardStates.clear();

	uint deviceCount;
	if (GetRawInputDeviceList(NULL, &deviceCount, sizeof(RAWINPUTDEVICELIST)) == -1)
	{
		logging::error("接続されているデバイス数の取得に失敗しました。", "initialize", "Device");
		return false;
	}

	m_RawInputDeviceLists.resize(deviceCount);
	if (GetRawInputDeviceList(m_RawInputDeviceLists.data(), &deviceCount, sizeof(RAWINPUTDEVICELIST)) == -1)
	{
		logging::error("接続されているデバイスの取得に失敗しました。", "initialize", "Device");
		return false;
	}

	for (uint i = 0; i < deviceCount; i++)
	{
		// DeviceIDを取得する
		uint nameSize;
		if (GetRawInputDeviceInfo(m_RawInputDeviceLists[i].hDevice, RIDI_DEVICENAME, NULL, &nameSize) == -1)
		{
			logging::error("DeviceIDのサイズの取得に失敗しました。", "initialize", "Device");
			return false;
		}

		std::string inputDeviceName;
		inputDeviceName.resize(nameSize);
		if (GetRawInputDeviceInfo(m_RawInputDeviceLists[i].hDevice, RIDI_DEVICENAME, &inputDeviceName[0], &nameSize) < 0)
		{
			logging::error("DeviceIDの取得に失敗しました。", "initialize", "Device");
			return false;
		}

		// RawInputで取得したDeviceIDから製品名を取得する
		std::string productName = inputDeviceName;
		HANDLE hid = CreateFile(inputDeviceName.data(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
		if (hid != INVALID_HANDLE_VALUE)
		{
			std::wstring wideProductName;
			wideProductName.resize(126);
			if (HidD_GetProductString(hid, &wideProductName[0], wideProductName.size()) != TRUE)
			{
				logging::error("製品名の取得に失敗しました。", "initialize", "Device");
			}
			CloseHandle(hid);

			productName = std::move(charset::narrow(wideProductName));
		}

		// デバイスの種類を調べる
		switch (m_RawInputDeviceLists[i].dwType)
		{
		// マウスデバイス
		case RIM_TYPEMOUSE:
		{
			mouse_state state;
			state.device_handle = m_RawInputDeviceLists[i].hDevice;
			state.name = productName;
			state.move = int3::zero();

			const uint keyCount = state.keys.size();
			for (uint j = 0; j < keyCount; j++)
			{
				state.keys[j].pressed = false;
				state.keys[j].released = false;
				state.keys[j].clicked = false;
			}

			m_MouseStates.push_back(std::move(state));
			break;
		}

		// キーボードデバイス
		case RIM_TYPEKEYBOARD:
		{
			keyboard_state state;
			state.device_handle = m_RawInputDeviceLists[i].hDevice;
			state.name = productName;

			const size_t keyCount = state.keys.size();
			for (size_t j = 0; j < keyCount; j++)
			{
				state.keys[j].pressed = false;
				state.keys[j].released = false;
				state.keys[j].clicked = false;
			}

			m_KeyboardStates.push_back(std::move(state));
			break;
		}
		}
	}

	return true;
}

bool device::register_window(HWND hwnd) const
{
	// WM_INPUTでメッセージを取得できるように設定
	RAWINPUTDEVICE rawInputDevice[2];
        
	// マウス
	rawInputDevice[0].usUsagePage = 0x01; 
	rawInputDevice[0].usUsage = 0x02; 
	rawInputDevice[0].dwFlags = 0;
	rawInputDevice[0].hwndTarget = hwnd;

	// キーボード
	rawInputDevice[1].usUsagePage = 0x01; 
	rawInputDevice[1].usUsage = 0x06;
	rawInputDevice[1].dwFlags = 0;
	rawInputDevice[1].hwndTarget = hwnd;

	if (RegisterRawInputDevices(rawInputDevice, 2, sizeof(RAWINPUTDEVICE) == FALSE))
	{
		logging::error("デバイスの登録に失敗しました。", "addWindow", "Device");
		return false;
	}
	return true;
}

void device::on_input(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	HRAWINPUT inputHandle = reinterpret_cast<HRAWINPUT>(lParam);

	uint size;
	if (GetRawInputData(inputHandle, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER)) == -1)
	{
		logging::error("入力データサイズの取得に失敗しました。", "onInput", "Device");
		return;
	}
	std::vector<RAWINPUT> inputs(size / sizeof(RAWINPUT));
	if (GetRawInputData(inputHandle, RID_INPUT, inputs.data(), &size, sizeof(RAWINPUTHEADER)) == -1)
	{
		logging::error("入力データの取得に失敗しました。", "onInput", "Device");
		return;
	}

	for (auto& input : inputs)
	{
		if (input.header.dwType == RIM_TYPEKEYBOARD)
		{
			// キーボードの入力イベント
			input_keyboard(input);
		}
		else if (input.header.dwType == RIM_TYPEMOUSE)
		{
			// マウスの入力イベント
			input_mouse(input);
		}
	}
}

bool device::supports_mouse() const
{
	return !m_MouseStates.empty();
}

bool device::supports_keyboard() const
{
	return !m_KeyboardStates.empty();
}

const std::vector<mouse_state>& device::get_mouse_states() const
{
	return m_MouseStates;
}

const std::vector<keyboard_state>& device::get_keyboard_states() const
{
	return m_KeyboardStates;
}

void device::input_mouse(RAWINPUT& input)
{
	for (auto& state : m_MouseStates)
	{
		// デバイスハンドルが一致した場合に処理
		if (state.device_handle == input.header.hDevice)
		{
			static const LONG keyDownMaskTable[] =
			{
				RI_MOUSE_BUTTON_1_DOWN,
				RI_MOUSE_BUTTON_2_DOWN,
				RI_MOUSE_BUTTON_3_DOWN,
				RI_MOUSE_BUTTON_4_DOWN,
				RI_MOUSE_BUTTON_5_DOWN,
			};
			static const LONG keyUpMaskTable[] =
			{
				RI_MOUSE_BUTTON_1_UP,
				RI_MOUSE_BUTTON_2_UP,
				RI_MOUSE_BUTTON_3_UP,
				RI_MOUSE_BUTTON_4_UP,
				RI_MOUSE_BUTTON_5_UP,
			};

			const uint keyCount = ARRAYSIZE(keyUpMaskTable);
			for (uint i = 0; i < keyCount; i++)
			{
				bool down = (input.data.mouse.usButtonFlags & keyDownMaskTable[i]) == keyDownMaskTable[i];
				bool up = (input.data.mouse.usButtonFlags & keyUpMaskTable[i]) == keyUpMaskTable[i];
				state.keys[i].clicked = state.keys[i].pressed ? false : down;
				state.keys[i].pressed = down;
				state.keys[i].released = up;
			}

			state.move.x = input.data.mouse.lLastX;
			state.move.y = input.data.mouse.lLastY;
			state.move.z = (input.data.mouse.usButtonFlags & RI_MOUSE_WHEEL) == RI_MOUSE_WHEEL ? static_cast<uint>(input.data.mouse.usButtonData) : 0;

			return;
		}
	}
}

void device::input_keyboard(RAWINPUT& input)
{
	for (auto& state : m_KeyboardStates)
	{
		// デバイスハンドルが一致した場合に処理
		if (state.device_handle == input.header.hDevice)
		{
			const size_t keyCount = state.keys.size();
			for (size_t i = 0; i < keyCount; i++)
			{
				bool down = (input.data.keyboard.Flags & RI_KEY_MAKE) == RI_KEY_MAKE;
				bool up = (input.data.keyboard.Flags & RI_KEY_BREAK) == RI_KEY_BREAK;
				state.keys[i].clicked = state.keys[i].pressed ? false : down;
				state.keys[i].released = state.keys[i].pressed ? up : false;
				state.keys[i].pressed = down;
			}

			return;
		}
	}
}