#pragma once

#define NOMINMAX

#include <vector>
#include <Windows.h>

#include "IO/Logging.h"
#include "input/input_state.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "math/vector3.h"

namespace arch
{

namespace rawinput
{

struct mouse_state
{
	HANDLE device_handle;				// �f�o�C�X�n���h��
	std::string name;					// �f�o�C�X��
	int3 move;							// �ړ���
	std::array<input_state, 0x08> keys;	// �L�[�̏��
};

struct keyboard_state
{
	HANDLE device_handle;				// �f�o�C�X�n���h��
	std::string name;					// �f�o�C�X��
	std::array<input_state, 0xff> keys;	// �L�[�̏��
};

class device
{
public:
	device();
	~device();

	bool	reset();
	bool	register_window(HWND hwnd) const;

	void	on_input(HWND hwnd, WPARAM wParam, LPARAM lParam);
	
	bool	supports_mouse() const;
	bool	supports_keyboard() const;

	const std::vector<mouse_state>& get_mouse_states() const;
	const std::vector<keyboard_state>& get_keyboard_states() const;

private:
	void	input_mouse(RAWINPUT& input);
	void	input_keyboard(RAWINPUT& input);

	std::vector<mouse_state>		m_MouseStates;
	std::vector<keyboard_state>		m_KeyboardStates;
	std::vector<RAWINPUTDEVICELIST>	m_RawInputDeviceLists;
};

}

}