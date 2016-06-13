#pragma once

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#define NOMINMAX

#include <array>
#include <vector>
#include <dinput.h>
#include <SetupAPI.h>

#include "kernel/charset.h"
#include "io/logging.h"
#include "math/vector3.h"
#include "input/input_state.h"

namespace arch
{

namespace directinput
{

struct mouse_state
{
	IDirectInputDevice8* handle;
	std::string name;
	int3 move;
	std::array<input_state, 8> keys;
};

struct keyboard_state
{
	IDirectInputDevice8* handle;
	std::string name;
	std::array<input_state, 256> keys;
};

struct joystick_state
{
	IDirectInputDevice8* handle;
	std::string name;
};

class device final
{
public:
	device();
	~device();

	bool initialize(HINSTANCE hInstance);
	void finalize();
	void update();
	void clear_devices();
	void enumerate_devices();
	void set_focus(HWND hwnd);

	const std::vector<mouse_state>& get_mouse_states() const;
	const std::vector<keyboard_state>& get_keyboard_states() const;
	const std::vector<joystick_state>& get_joystick_states() const;

	static BOOL	CALLBACK enumerate_mouses_callback(const DIDEVICEINSTANCE* pDeviceInstance, void* pRef);
	static BOOL	CALLBACK enumerate_keyboards_callback(const DIDEVICEINSTANCE* pDeviceInstance, void* pRef);
	static BOOL	CALLBACK enumerate_joysticks_callback(const DIDEVICEINSTANCE* pDeviceInstance, void* pRef);

private:
	IDirectInputDevice8* create_device(const GUID Guid);
	void update_mouse(mouse_state& state);
	void update_keyboard(keyboard_state& state);
	void update_joystick(joystick_state& state);
	static std::string guid_to_device_name(const GUID Guid);

private:
	bool						m_HasInitialized;
	IDirectInput8*				m_pInput;			//DirectInputインターフェース
	std::vector<mouse_state>	m_MouseStates;		//
	std::vector<keyboard_state>	m_KeyboardStates;	//
	std::vector<joystick_state>	m_JoystickStates;	//
};

}

}