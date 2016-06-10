#pragma once

#include <string>
#include <memory>
#include <vector>
#include "input/midi.h"

namespace arch
{

namespace win32
{

class midi_device final
{
public:
	static midi_device& get_instance();

	void initalize();
	void finalize();

private:
	midi_device();
	~midi_device();

	class impl;
	std::unique_ptr<impl> pimpl;
	static midi_device instance;
};

}

}
