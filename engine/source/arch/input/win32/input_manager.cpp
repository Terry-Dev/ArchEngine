#include <cassert>
#include "kernel/convert.h"
#include "kernel/string_format.h"
#include "win32/input_manager.h"

using namespace arch;
using namespace arch::win32;

namespace
{
	uint to_direct_input_key_code(uint number)
	{
		static const uint direct_input_key_codes[] =
		{
			0x1E,	///< A
			0x30,	///< B
			0x2E,	///< C
			0x20,	///< D
			0x12,	///< E
			0x21,	///< F
			0x22,	///< G
			0x23,	///< H
			0x17,	///< I
			0x24,	///< J
			0x25,	///< K
			0x26,	///< L
			0x32,	///< M
			0x31,	///< N
			0x18,	///< O
			0x19,	///< P
			0x10,	///< Q
			0x13,	///< R
			0x1F,	///< S
			0x14,	///< T
			0x16,	///< U
			0x2F,	///< V
			0x11,	///< W
			0x2D,	///< X
			0x15,	///< Y
			0x2C,	///< Z

			0x0B,	///< 0
			0x02,	///< 1
			0x03,	///< 2
			0x04,	///< 3
			0x05,	///< 4
			0x06,	///< 5
			0x07,	///< 6
			0x08,	///< 7
			0x09,	///< 8
			0x0A,	///< 9
			0x01,	///< Esc
			0x3B,	///< F1
			0x3C,	///< F2
			0x3D,	///< F3
			0x3E,	///< F4
			0x3F,	///< F5
			0x40,	///< F6
			0x41,	///< F7
			0x42,	///< F8
			0x43,	///< F9
			0x44,	///< F10
			0x57,	///< F11
			0x58,	///< F12
			0x52,	///< テンキーの0
			0x4F,	///< テンキーの1
			0x50,	///< テンキーの2
			0x51,	///< テンキーの3
			0x4B,	///< テンキーの4
			0x4C,	///< テンキーの5
			0x4D,	///< テンキーの6
			0x47,	///< テンキーの7
			0x48,	///< テンキーの8
			0x49,	///< テンキーの9
			0x53,	///< テンキーの.
			0xB5,	///< テンキーの/
			0x37,	///< テンキーの*
			0x4E,	///< テンキーの+
			0x4A,	///< テンキーの-
			0x9C,	///< テンキーのEnter
			0xC8,	///< 上
			0xD0,	///< 下
			0xCB,	///< 左
			0xCD,	///< 右
			0x0C,	///< -
			0x0D,	///< =
			0x0F,	///< Tab
			0x27,	///< ;
			0x28,	///< '
			0x29,	///< `
			0x1C,	///< Enter
			0x0E,	///< BackSpace
			0x39,	///< Space
			0x1A,	///< [
			0x1B,	///< ]
			0x1D,	///< 左Ctrl
			0x9D,	///< 右Ctrl
			0x2A,	///< 左Shift
			0x36,	///< 右Shift
			0x38,	///< 左Alt
			0xB8,	///< 右Alt
			0x35,	///< /
			0x2B,	///< ＼
			0x33,	///< ,
			0x34,	///< .
		};

		return direct_input_key_codes[number];
	}

	uint to_win32_virtual_key_code(uint code)
	{
		static const uint key_codes[] =
		{
			0x41,	///< A
			0x42,	///< B
			0x43,	///< C
			0x44,	///< D
			0x45,	///< E
			0x46,	///< F
			0x47,	///< G
			0x48,	///< H
			0x49,	///< I
			0x4A,	///< J
			0x4B,	///< K
			0x4C,	///< L
			0x4D,	///< M
			0x4E,	///< N
			0x4F,	///< O
			0x50,	///< P
			0x51,	///< Q
			0x52,	///< R
			0x53,	///< S
			0x54,	///< T
			0x55,	///< U
			0x56,	///< V
			0x57,	///< W
			0x58,	///< X
			0x59,	///< Y
			0x5A,	///< Z

			0x30,	///< 0
			0x31,	///< 1
			0x32,	///< 2
			0x33,	///< 3
			0x34,	///< 4
			0x35,	///< 5
			0x36,	///< 6
			0x37,	///< 7
			0x38,	///< 8
			0x39,	///< 9

			0x1B,	///< Esc

			0x70,	///< F1
			0x71,	///< F2
			0x72,	///< F3
			0x73,	///< F4
			0x74,	///< F5
			0x75,	///< F6
			0x76,	///< F7
			0x77,	///< F8
			0x78,	///< F9
			0x79,	///< F10
			0x7A,	///< F11
			0x7B,	///< F12

			0x60,	///< テンキーの0
			0x61,	///< テンキーの1
			0x62,	///< テンキーの2
			0x63,	///< テンキーの3
			0x64,	///< テンキーの4
			0x65,	///< テンキーの5
			0x66,	///< テンキーの6
			0x67,	///< テンキーの7
			0x68,	///< テンキーの8
			0x69,	///< テンキーの9
			0x6E,	///< テンキーの.
			0x6F,	///< テンキーの/
			0x6A,	///< テンキーの*
			0x6B,	///< テンキーの+
			0x6D,	///< テンキーの-
			0x00,	///< テンキーのEnter

			0x26,	///< 上
			0x28,	///< 下
			0x25,	///< 左
			0x27,	///< 右

			0xBD,	///< -
			0x00,	///< =
			0x09,	///< Tab
			0x00,	///< ;
			0x00,	///< '
			0x00,	///< `

			0x0D,			///< Enter
			0x08,		///< BackSpace
			0x20,			///< Space

			0xDB,	///< [
			0xDD,	///< ]
			0xA2,	///< 左Ctrl
			0xA3,	///< 右Ctrl
			0xA0,	///< 左Shift
			0xA1,	///< 右Shift
			0xA4,	///< 左Alt
			0xA5,	///< 右Alt
			0x5B,	///< 左Windows
			0x5C,	///< 右Windows

			0xBF,	///< /
			0xDC,	///< ＼

			0xBC,	///< ,
			0xBE,	///< .

			0x14,	///< CapsLock
			0x90,	///< NumLock
			0x91,	///< ScrollLock

			0x15,	///< かな入力
			0x1C,	///< 変換
			0x1D,	///< 無変換
			0xDC,	///< \

			0x00,	///< SysRq
			0x13,	///< Pause

			0x2D,	///< Insert
			0x2E,	///< Delete
			0x24,	///< Home
			0x23,	///< End
			0x21,	///< PageUp
			0x22,	///< PageDown
		};

		return key_codes[code];
	}
}

input_manager input_manager::instance;

input_manager::input_manager()
{
}

input_manager::~input_manager()
{
}

input_manager& input_manager::get_instance()
{
	return instance;
}

bool input_manager::initialize(HINSTANCE hInstance)
{
	// DirectInputを初期化
	if (m_DirectInput.initialize(hInstance))
	{
		logging::infomation("DirectInputを使用します。");

		const auto& mouseStates = m_DirectInput.get_mouse_states();
		for (const auto& state : mouseStates)
		{
			logging::debug(state.name);
		}

		const auto& keyboardStates = m_DirectInput.get_keyboard_states();
		for (const auto& state : keyboardStates)
		{
			logging::debug(state.name);
		}

		const auto& joystickStates = m_DirectInput.get_joystick_states();
		for (const auto& state : joystickStates)
		{
			logging::debug(state.name);
		}
	}

	if (m_Wintab.initialize())
	{
		logging::infomation(string_format("Wintabを使用できます。(Version:%d)", m_Wintab.getVersion()));
		pen::supports = true;

		const auto& maxPosition = m_Wintab.getMaxPosition();
		const auto& minPosition = m_Wintab.getMinPosition();
		logging::infomation(string_format("WACOM Tablet (Max:%s, Min:%s)", convert::to_string(maxPosition).data(), convert::to_string(minPosition).data()));

		if (m_Wintab.supportsPressure())
		{
			const auto& pressure = m_Wintab.getPressureInfo();
			logging::infomation(string_format("筆圧を利用できます。(Max:%d, Min:%d, Resolution:%d)", pressure.max, pressure.min, pressure.resolution));
			pen::supports_pressure = true;
		}

		if (m_Wintab.supportsTilt())
		{
			const auto& altitude = m_Wintab.getAltitudeInfo();
			const auto& azimuth = m_Wintab.getAzimuthInfo();
			logging::infomation(string_format("傾きを利用できます。Altitude(Max:%d, Min:%d, Resolution:%d) Azimuth(Max:%d, Min:%d, Resolution:%d)", altitude.max, altitude.min, altitude.resolution, azimuth.max, azimuth.min, azimuth.resolution));
			pen::supports_tilt = true;
		}
	}

	/*
	m_RawInputManager.reset();

	const auto& mouseStates = m_RawInputManager.getMouseStates();
	for (const auto& state : mouseStates)
	{
		logging::infomation(state.name);
	}

	const auto& keyboardStates = m_RawInputManager.getKeyboardStates();
	for (const auto& state : keyboardStates)
	{
		logging::infomation(state.name);
	}
	*/
	return true;
}

void input_manager::finalize()
{
	m_DirectInput.finalize();

	for (auto& info : m_WindowInfos)
	{
		SetWindowLongPtrW(info.handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(info.defProc));
	}
	m_WindowInfos.clear();
}

bool input_manager::update()
{
	// DirectInputを更新
	m_DirectInput.update();

	std::array<input_state*, 8> mouse_state_refs =
	{
		&mouse::button1,
		&mouse::button2,
		&mouse::button3,
		&mouse::button4,
		&mouse::button5,
		&mouse::button6,
		&mouse::button7,
		&mouse::button8,
	};

	// デフォルトは0番目の状態を用いる
	const auto& mouseStates = m_DirectInput.get_mouse_states();
	if (!mouseStates.empty())
	{
		for (uint i = 0; i < mouse_state_refs.size(); i++)
		{
			*mouse_state_refs[i] = mouseStates[0].keys[i];
		}
		mouse::move = mouseStates[0].move;
		mouse::left = mouseStates[0].keys[0];
		mouse::right = mouseStates[0].keys[1];
	}

	std::array<input_state*, 90> keyboard_state_refs =
	{
		&keyboard::key_A,
		&keyboard::key_B,
		&keyboard::key_C,
		&keyboard::key_D,
		&keyboard::key_E,
		&keyboard::key_F,
		&keyboard::key_G,
		&keyboard::key_H,
		&keyboard::key_I,
		&keyboard::key_J,
		&keyboard::key_K,
		&keyboard::key_L,
		&keyboard::key_M,
		&keyboard::key_N,
		&keyboard::key_O,
		&keyboard::key_P,
		&keyboard::key_Q,
		&keyboard::key_R,
		&keyboard::key_S,
		&keyboard::key_T,
		&keyboard::key_U,
		&keyboard::key_V,
		&keyboard::key_W,
		&keyboard::key_X,
		&keyboard::key_Y,
		&keyboard::key_Z,

		&keyboard::key_0,
		&keyboard::key_1,
		&keyboard::key_2,
		&keyboard::key_3,
		&keyboard::key_4,
		&keyboard::key_5,
		&keyboard::key_6,
		&keyboard::key_7,
		&keyboard::key_8,
		&keyboard::key_9,

		&keyboard::key_f1,
		&keyboard::key_f2,
		&keyboard::key_f3,
		&keyboard::key_f4,
		&keyboard::key_f5,
		&keyboard::key_f6,
		&keyboard::key_f7,
		&keyboard::key_f8,
		&keyboard::key_f9,
		&keyboard::key_f10,
		&keyboard::key_f11,
		&keyboard::key_f12,

		&keyboard::key_num_0,
		&keyboard::key_num_1,
		&keyboard::key_num_2,
		&keyboard::key_num_3,
		&keyboard::key_num_4,
		&keyboard::key_num_5,
		&keyboard::key_num_6,
		&keyboard::key_num_7,
		&keyboard::key_num_8,
		&keyboard::key_num_9,

		&keyboard::key_num_period,
		&keyboard::key_num_divide,
		&keyboard::key_num_multiply,
		&keyboard::key_num_plus,
		&keyboard::key_num_minus,
		&keyboard::key_num_enter,

		&keyboard::key_escape,

		&keyboard::key_up,
		&keyboard::key_down,
		&keyboard::key_left,
		&keyboard::key_right,

		&keyboard::key_minus,
		&keyboard::key_equals,
		&keyboard::key_tab,
		&keyboard::key_semicolon,
		&keyboard::key_apostrophe,
		&keyboard::key_back_quote,

		&keyboard::key_enter,
		&keyboard::key_backspace,
		&keyboard::key_space,

		&keyboard::key_left_bracket,
		&keyboard::key_right_bracket,
		&keyboard::key_left_control,
		&keyboard::key_right_control,
		&keyboard::key_left_shift,
		&keyboard::key_right_shift,
		&keyboard::key_left_alt,
		&keyboard::key_right_alt,

		&keyboard::key_slash,
		&keyboard::key_backslash,

		&keyboard::key_comma,
		&keyboard::key_period,
	};

	const auto& keyboardStates = m_DirectInput.get_keyboard_states();
	if (!keyboardStates.empty())
	{
		for (uint i = 0; i < keyboard_state_refs.size(); i++)
		{
			auto key_code = to_direct_input_key_code(i);
			*keyboard_state_refs[i] = keyboardStates[0].keys[key_code];
		}
	}

	pen::is_eraser = m_Wintab.isEraser();

	return true;
}

void input_manager::add_window_handle(HWND hwnd)
{
	WindowInfo info;
	info.defProc	= reinterpret_cast<WNDPROC>(GetWindowLongPtrW(hwnd, GWLP_WNDPROC));
	info.handle		= hwnd;

	m_WindowInfos.push_back(info);

	RegisterTouchWindow(hwnd, 0);
	SetWindowLongPtrW(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(input_manager::GlobalWndProc));

	m_DirectInput.set_focus(hwnd);

	if (m_Wintab.supportsWintab())
	{
		m_Wintab.registerWindow(hwnd);
	}

	//m_Rawinput_manager.registerWindow(hwnd);
}

bool input_manager::supports_touch() const
{
	return GetSystemMetrics(SM_DIGITIZER) != 0;
}

bool input_manager::supports_multi_touch() const
{
	return (GetSystemMetrics(SM_DIGITIZER) & NID_MULTI_INPUT) == NID_MULTI_INPUT;
}

LRESULT CALLBACK input_manager::GlobalWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return instance.localWndProc(hwnd, uMsg, wParam, lParam);
}


LRESULT input_manager::localWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	/*
	// 入力イベント(RawInput)
	case WM_INPUT:
		m_Rawinput_manager.onInput(hwnd, wParam, lParam);
		onUpdateMouse();
		break;
	*/
	// 入力イベント(Wintab)
	case WT_PACKET:
	case WT_CSRCHANGE:
	case WT_CTXOPEN:
	case WT_CTXUPDATE:
	case WT_CTXOVERLAP:
	case WT_PROXIMITY:
	case WT_INFOCHANGE:
	case WM_ACTIVATE:
		m_Wintab.onMessage(hwnd, uMsg, wParam, lParam);
		onUpdatePen();
		return 0;

	// タッチ入力イベント
	case WM_TOUCH:
		onTouch(hwnd, wParam, lParam);
		return 0;

	// マウス移動イベント
	case WM_MOUSEMOVE:
		// イベント処理
		onMouseMove(hwnd, wParam, lParam);
		break;

	/*
	// 左ボタン押下イベント
	case WM_LBUTTONDOWN:
		onLButtonDown(hwnd, wParam, lParam);
		return 0;

	// 左ボタン押上イベント
	case WM_LBUTTONUP:
		onLButtonUp(hwnd, wParam, lParam);
		return 0;
	*/
	/*
	case WM_KEYDOWN:
		//WMKeyDown(wParam);
		break;

	//キーが押され文字が入力された場合
	case WM_CHAR:
		//WMChar(wParam);
		break;

	case WM_IME_SETCONTEXT:			//IMEウィンドウの状態変化
		//lParam = 0;
		break;

	case WM_IME_STARTCOMPOSITION:	//IMEの入力受付開始
		//m_EditFlag = true;
		break;

	case WM_IME_ENDCOMPOSITION:		//IMEの入力受付終了
		//m_EditFlag = false;
		//m_EditString = L"\0";
		//m_EditInputPosition = 0;
		break;

	case WM_IME_COMPOSITION:		//IMEの入力された文字が変化
		//Composition(lParam);
		break;

	case WM_IME_NOTIFY:				//IMEの状態が変化
		//Notify(wParam);
		break;
	*/
	}

	for (const auto& info : m_WindowInfos)
	{
		if (info.handle == hwnd)
		{
			return CallWindowProc(info.defProc, hwnd, uMsg, wParam, lParam);
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void input_manager::onLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	const LPARAM MouseEventfromTouch = 0xff515700;
	const LPARAM TouchEventfromTouch = 0x80;

	// イベントがタッチイベントかどうか判定
	auto extraInfo = GetMessageExtraInfo();
	if ((extraInfo & MouseEventfromTouch) == MouseEventfromTouch)
	{
		// タッチによるイベントかペンによるイベントか判定
		if ((extraInfo & TouchEventfromTouch) == TouchEventfromTouch)
		{
			// タッチイベント
		}
		else
		{
			// ペンイベント
		}
	}
	else
	{
		// マウスイベント
		mouse::left.pressed = true;
		mouse::left.released = false;
		mouse::left.clicked = false;
	}
}

void input_manager::onLButtonUp(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	const LPARAM MouseEventfromTouch = 0xff515700;
	const LPARAM TouchEventfromTouch = 0x80;

	// イベントがタッチイベントかどうか判定
	auto extraInfo = GetMessageExtraInfo();
	if ((extraInfo & MouseEventfromTouch) == MouseEventfromTouch)
	{
		// タッチによるイベントかペンによるイベントか判定
		if ((extraInfo & TouchEventfromTouch) == TouchEventfromTouch)
		{
			// タッチイベント
		}
		else
		{
			// ペンイベント
		}
	}
	else
	{
		// マウスイベント
		mouse::left.pressed = false;
		mouse::left.released = true;
		mouse::left.clicked = false;
	}
}

void input_manager::onMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	POINT point;

	// カーソルの位置を取得
	if(GetCursorPos(&point) == FALSE)
	{
		return;
	}

	// クライアント領域の左上から見たマウス座標を算出
	if(ScreenToClient(hwnd, &point) == FALSE)
	{
		return;
	}

	mouse::position.x = point.x;
	mouse::position.y = point.y;
}

void input_manager::onTouch(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	uint inputCount = LOWORD(wParam);
	HTOUCHINPUT	inputHandle = reinterpret_cast<HTOUCHINPUT>(lParam);
	std::vector<TOUCHINPUT> inputs(inputCount);

	if (GetTouchInputInfo(inputHandle, inputCount, inputs.data(), sizeof(TOUCHINPUT)))
	{
		touch::infos.resize(inputCount);
		for (uint i = 0; i < inputCount; i++)
		{
			POINT point;
			point.x = TOUCH_COORD_TO_PIXEL(inputs[i].x);
			point.y = TOUCH_COORD_TO_PIXEL(inputs[i].x);
			ScreenToClient(hwnd, &point);

			touch::infos[i].id = inputs[i].dwID;
			touch::infos[i].state.released = (inputs[i].dwFlags & TOUCHEVENTF_UP) == TOUCHEVENTF_UP;
			touch::infos[i].state.clicked = touch::infos[i].state.pressed ? touch::infos[i].state.released : false;
			touch::infos[i].state.pressed = (inputs[i].dwFlags & TOUCHEVENTF_DOWN) == TOUCHEVENTF_DOWN;
			touch::infos[i].position.x = point.x;
			touch::infos[i].position.y = point.y;
			touch::infos[i].move = double2::zero();

			// 移動イベントの場合は移動量の更新を行う
			if ((inputs[i].dwFlags & TOUCHEVENTF_MOVE) == TOUCHEVENTF_MOVE)
			{
				for (auto& prevInput : m_PreviousTouchInputs)
				{
					// 前回の入力イベントがあった場合は前回の位置から移動量を算出
					if (inputs[i].dwID == prevInput.dwID)
					{
						touch::infos[i].move.x = static_cast<double>(inputs[i].x - prevInput.x) / 100.0;
						touch::infos[i].move.y = static_cast<double>(inputs[i].y - prevInput.y) / 100.0;
						break;
					}
				}
			}
		}
		m_PreviousTouchInputs = std::move(inputs);
    }

	CloseTouchInputHandle(inputHandle);
}

void input_manager::onUpdateMouse() const
{
	// イベント処理後の値を更新
	const auto& states = m_RawInput.get_mouse_states();
	if (states.empty())
	{
		return;
	}

	// デフォルトは全てのマウスの状態を用いる
	/*
	for (const auto& state : states)
	{
		mouse::move = max(state.move, mouse::move);

		for (uint i = 0; i < state.keys.size(); i++)
		{
			mouse::keys[i].pressed = mouse::keys[i].pressed ? mouse::keys[i].pressed : state.keys[i].pressed;
			mouse::keys[i].released = mouse::keys[i].released ? mouse::keys[i].released : state.keys[i].released;
			mouse::keys[i].clicked = mouse::keys[i].clicked ? mouse::keys[i].clicked : state.keys[i].clicked;
		}
	}
	*/
}

void input_manager::onUpdateKeyboard() const
{
	// イベント処理後の値を更新
	const auto& states = m_RawInput.get_keyboard_states();
	if (states.empty())
	{
		return;
	}

	// デフォルトは0番目の状態
	/*
	const size_t keyCount = keyboard::keys.size();
	for (uint i = 0; i < keyCount; i++)
	{
		keyboard::keys[i] = states[0].keys[i];
	}
	*/
}

void input_manager::onUpdatePen() const
{
	pen::pressure = m_Wintab.getPressure();
	pen::altitude = m_Wintab.getAltitudeRadian();
	pen::azimuth = m_Wintab.getAzimuthRadian();
}

