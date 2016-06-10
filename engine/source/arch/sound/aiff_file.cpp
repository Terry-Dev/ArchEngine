//=================================================================================//
//                                                                                 //
//  ArchEngine                                                                     //
//                                                                                 //
//  Copyright (C) 2011-2016 Terry                                                  //
//                                                                                 //
//  This file is a portion of the ArchEngine. It is distributed under the MIT      //
//  License, available in the root of this distribution and at the following URL.  //
//  http://opensource.org/licenses/mit-license.php                                 //
//                                                                                 //
//=================================================================================//

#include "math_function.h"
#include "endian.h"
#include "aiff_file.h"

using namespace arch;

aiff_reader::aiff_reader()
: m_format{0}
{
}

aiff_reader::aiff_reader(const std::string& path)
: aiff_reader()
{
	m_reader = iff_reader(path);
	if (!m_reader)
	{
		return;
	}

	const std::string aiff_chunk_name = "AIFF";
	const std::string common_chunk_name = "COMM";
	const std::string data_chunk_name = "SSND";

	if (m_reader.form_type() != aiff_chunk_name)
	{
		m_reader.close();
		return;
	}

	if (!m_reader.seek(common_chunk_name))
	{
		m_reader.close();
		return;
	}

	const uint32_t fmt_size = m_reader.size();
	if (fmt_size != 18)
	{
		m_reader.close();
		return;
	}

	uint16_t extend[5];

	m_format.channels = endian::swap(m_reader.read<uint16_t>());
	m_format.sample_frames = endian::swap(m_reader.read<uint32_t>());
	m_format.sample_size = endian::swap(m_reader.read<uint16_t>());

	for (int i = 0; i < 5; i++)
	{
		extend[i] = endian::swap(m_reader.read<uint16_t>());
	}
	
	m_format.sampling_rate = extend[1] << (2 * (extend[0] - 16398));

	if (!m_reader.seek(data_chunk_name))
	{
		m_reader.close();
		return;
	}
}

void aiff_reader::close()
{
	m_reader.close();
}

size_t aiff_reader::read(void* buffer, size_t size)
{
	size_t real_size = 0;
	switch (m_format.sample_size)
	{
	case 8:
	{
		int8_t data;
		int8_t* out = reinterpret_cast<int8_t*>(buffer);
		while (real_size < size)
		{
			size_t read_size = m_reader.read(&data, sizeof(data));
			if (read_size == 0)
			{
				break;
			}
			out[real_size] = endian::swap(data);
			real_size += read_size;
		}
		break;
	}
	case 16:
	{
		int16_t data;
		int16_t* out = reinterpret_cast<int16_t*>(buffer);
		while (real_size < size)
		{
			size_t read_size = m_reader.read(&data, sizeof(data));
			if (read_size == 0)
			{
				break;
			}
			out[real_size / sizeof(data)] = endian::swap(data);
			real_size += read_size;
		}
		break;
	}
	case 32:
	{
		int32_t data;
		int32_t* out = reinterpret_cast<int32_t*>(buffer);
		while (real_size < size)
		{
			size_t read_size = m_reader.read(&data, sizeof(data));
			if (read_size == 0)
			{
				break;
			}
			out[real_size / sizeof(data)] = endian::swap(data);
			real_size += read_size;
		}
		break;
	}
	}

	return real_size;
}

bool aiff_reader::seek(size_t samples)
{
	return m_reader.seek(samples);
}

size_t aiff_reader::tell() const
{
	return m_reader.tell();
}

uint32_t aiff_reader::size() const
{
	return m_reader.size();
}

const aiff_format& aiff_reader::format() const
{
	return m_format;
}

bool aiff_reader::is_opened() const
{
	return m_reader.is_opened();
}

bool aiff_reader::end() const
{
	return m_reader.end();
}

bool aiff_reader::operator!() const
{
	return !m_reader;
}