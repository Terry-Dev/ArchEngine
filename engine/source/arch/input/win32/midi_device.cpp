#define NOMINMAX

#include <array>
#include <map>
#include <Windows.h>
#include <mmsystem.h>
#include "win32/midi_device.h"

#pragma comment(lib, "winmm.lib")

using namespace arch;
using namespace arch::midi;
using namespace arch::win32;

class midi_device::impl
{
public:
	struct midi_in_handle
	{
		HMIDIIN handle;
		MIDIHDR header;
		std::array<char, 256> buffer;
		std::vector<message> messages;
	};

public:
	impl();
	~impl();

	uint create_midi_in(uint id);
	void release_midi_in(HMIDIIN handle);

	static void CALLBACK global_callback(HMIDIIN midi_in_handle, UINT msg, DWORD midi_instance, DWORD param1, DWORD param2);

private:


	void midi_in_callback(midi_in_handle handle, UINT msg, DWORD midi_instance, DWORD param1, DWORD param2);

	static impl instance;
	std::map<HMIDIIN, midi_in_handle> midi_in_handles;
};

midi_device::impl midi_device::impl::instance;

midi_device::impl::impl()
{
}

midi_device::impl::~impl()
{

}

uint midi_device::impl::create_midi_in(uint id)
{
	midi_in_handle handle;
	if (midiInOpen(&handle.handle, id, reinterpret_cast<DWORD_PTR>(global_callback), 0, CALLBACK_FUNCTION | MIDI_IO_STATUS) != MMSYSERR_NOERROR)
	{
		return 0;
	}
	handle.header.lpData = handle.buffer.data();
	handle.header.dwBufferLength = static_cast<DWORD>(handle.buffer.size());

	midi_in_handles.insert(std::make_pair(handle.handle, std::move(handle)));

	midiInPrepareHeader(handle.handle, &handle.header, sizeof(MIDIHDR));
	midiInAddBuffer(handle.handle, &handle.header, sizeof(MIDIHDR));
	midiInStart(handle.handle);

	return reinterpret_cast<uint>(handle.handle);
}

void midi_device::impl::release_midi_in(HMIDIIN handle)
{
	auto itr = instance.midi_in_handles.find(handle);
	if (itr != instance.midi_in_handles.end())
	{
		return;
	}
}

void CALLBACK midi_device::impl::global_callback(HMIDIIN midi_in_handle, UINT msg, DWORD midi_instance, DWORD param1, DWORD param2)
{
	auto itr = instance.midi_in_handles.find(midi_in_handle);
	if (itr != instance.midi_in_handles.end())
	{
		return;
	}

	instance.midi_in_callback(itr->second, msg, midi_instance, param1, param2);
}

void midi_device::impl::midi_in_callback(midi_in_handle handle, UINT msg, DWORD midi_instance, DWORD param1, DWORD param2)
{
	message midi_msg;
	switch (msg)
	{
	case MIM_DATA:
		midi_msg.status = static_cast<uint8_t>(param1 & 0xff);
		midi_msg.data[0] = static_cast<uint8_t>((param1 >> 8) & 0xff);
		midi_msg.data[1] = static_cast<uint8_t>((param1 >> 16) & 0xff);
		handle.messages.push_back(std::move(midi_msg));
		break;

	case MIM_LONGDATA:
		if (handle.header.dwBytesRecorded == 0)
		{
			return;
		}

		for (DWORD i = 0; i < handle.header.dwBytesRecorded; i++)
		{
		}

		midiInPrepareHeader(handle.handle, &handle.header, sizeof(MIDIHDR));
		midiInAddBuffer(handle.handle, &handle.header, sizeof(MIDIHDR));

		break;
	}
}


midi_device::midi_device()
{
}

midi_device::~midi_device()
{
}

midi_device& midi_device::get_instance()
{
	return instance;
}

/*
bool midi_device::finalize(HMIDIIN hMIDI)
{
	stop(hMIDI);
	reset(hMIDI);
	auto itr = MIDIInputMap.find(hMIDI);
	if (itr != MIDIInputMap.end())
	{
		MIDIInputMap.erase(itr);
	}
	return midiInClose(hMIDI) == MMSYSERR_NOERROR;
}
bool midi_device::finalize(unsigned int deviceID)
{
	HMIDIIN hMIDI = getMIDIInput(deviceID);
	if (hMIDI != nullptr)
	{
		return finalize(hMIDI);
	}
	return false;
}
HMIDIIN midi_device::getMIDIInput(unsigned int deviceID)
{
	for each (auto var in MIDIInputMap)
	{
		if (var.second->getDeviceID() == deviceID)
		{
			return var.first;
		}
	}
	return nullptr;
}

bool midi_device::start(HMIDIIN hMIDI)
{
}

bool midi_device::start(unsigned int deviceID)
{
	return start(getMIDIInput(deviceID));
}
void midi_device::start()
{
	for each (auto var in MIDIInputMap)
	{
		start(var.first);
	}
}
bool midi_device::stop(HMIDIIN hMIDI)
{
	return midiInStop(hMIDI) == MMSYSERR_NOERROR;
}
bool midi_device::stop(unsigned int deviceID)
{
	return stop(getMIDIInput(deviceID));
}
void midi_device::stop()
{
	for each (auto var in MIDIInputMap)
	{
		stop(var.first);
	}
}
bool midi_device::reset(HMIDIIN hMIDI)
{
	return midiInReset(hMIDI) == MMSYSERR_NOERROR;
}
bool midi_device::reset(unsigned int deviceID)
{
	return reset(getMIDIInput(deviceID));
}
void midi_device::reset()
{
	for each (auto var in MIDIInputMap)
	{
		reset(var.first);
	}
}

void midi_device::MIDIInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{

}

vector<std::string> midi_device::getDeviceList()
{
	vector<std::string> result;
	unsigned int num = midiInGetNumDevs();
	MIDIINCAPS caps;
	for (size_t i = 0; i < num; i++)
	{
		midiInGetDevCaps(i, &caps, sizeof(caps));
		result.push_back(caps.szPname);
	}
	return move(result);
}
*/