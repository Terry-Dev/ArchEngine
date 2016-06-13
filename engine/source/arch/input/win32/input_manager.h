#pragma once

#include <vector>
#include "rawinput/rawinput_device.h"
#include "directinput/directinput_device.h"
#include "wintab/wintab_device.h"
#include "input/keyboard.h"
#include "input/mouse.h"
#include "input/touch.h"
#include "input/pen.h"

namespace arch
{

namespace win32
{

class input_manager final
{
public:
	static input_manager& get_instance();

	bool initialize(HINSTANCE hInstance);
	void finalize();
	bool update();

	void add_window_handle(HWND hwnd);

	bool supports_touch() const;
	bool supports_multi_touch() const;

	static LRESULT CALLBACK	GlobalWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	///< グローバルウィンドウプロシージャ

private:
	input_manager();
	~input_manager();

	LRESULT localWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);					///< ローカルウィンドウプロシージャ

	void onLButtonDown(HWND hwnd, WPARAM wParam, LPARAM lParam);
	void onLButtonUp(HWND hwnd, WPARAM wParam, LPARAM lParam);
	void onMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam);
	void onTouch(HWND hwnd, WPARAM wParam, LPARAM lParam);
	void onUpdateMouse() const;
	void onUpdateKeyboard() const;
	void onUpdatePen() const;

private:
	struct WindowInfo
	{
		WNDPROC defProc;
		HWND handle;
	};

	static input_manager instance;

	bool						m_HasInitialized;
	std::vector<WindowInfo>		m_WindowInfos;
	std::vector<TOUCHINPUT>		m_PreviousTouchInputs;
	directinput::device			m_DirectInput;
	rawinput::device			m_RawInput;
	wintab::device				m_Wintab;
};

}

}