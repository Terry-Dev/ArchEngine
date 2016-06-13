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

#include "arch/wave_file.h"

using namespace arch;

wave_reader::wave_reader()
: m_format{0}
{
}

wave_reader::wave_reader(const std::string& path)
: wave_reader()
{
	m_reader = riff_reader(path);
	if (!m_reader)
	{
		return;
	}

	const std::string wave_chunk_name = "WAVE";
	const std::string fmt_chunk_name = "fmt ";
	const std::string data_chunk_name = "data";

	if (m_reader.form_type() != wave_chunk_name)
	{
		m_reader.close();
		return;
	}

	if (!m_reader.seek(fmt_chunk_name))
	{
		m_reader.close();
		return;
	}

	const uint32_t fmt_size = m_reader.size();
	if (fmt_size != 16)
	{
		m_reader.close();
		return;
	}

	m_format = m_reader.read<wave_format>();
	if (m_format.format_id != 1)
	{
		const uint16_t extention_size = m_reader.read<uint16_t>();
		//m_reader.seek(static_cast<size_t>(extention_size), seek_origin::current);
	}
	
	if (!m_reader.seek(data_chunk_name))
	{
		m_reader.close();
		return;
	}
}

void wave_reader::close()
{
	m_reader.close();
}

size_t wave_reader::read(void* buffer, size_t size)
{
	return m_reader.read(buffer, size);
}

bool wave_reader::seek(size_t samples)
{
	return m_reader.seek(samples);
}

size_t wave_reader::tell() const
{
	return m_reader.tell();
}

uint32_t wave_reader::size() const
{
	return m_reader.size();
}

const wave_format& wave_reader::format() const
{
	return m_format;
}

bool wave_reader::is_opened() const
{
	return m_reader.is_opened();
}

bool wave_reader::end() const
{
	return m_reader.end();
}

bool wave_reader::operator!() const
{
	return !m_reader;
}


wave_writer::wave_writer()
: m_extention_size(0), m_data_size(0)
{
}

wave_writer::wave_writer(const std::string& path, const wave_format& format)
: wave_writer()
{
	m_writer = binary_writer(path);
	if (!m_writer)
	{
		return;
	}

	const std::string riff_chunk_name = "RIFF";
	const std::string wave_chunk_name = "WAVE";
	const std::string fmt_chunk_name = "fmt ";
	const std::string data_chunk_name = "data";

	const uint16_t file_size = 0;
	const uint32_t fmt_size = sizeof(wave_format);

	m_writer.write(riff_chunk_name.data(), riff_chunk_name.size());
	m_writer.write<uint32_t>(file_size);
	m_writer.write(wave_chunk_name.data(), wave_chunk_name.size());
	m_writer.write(fmt_chunk_name.data(), fmt_chunk_name.size());
	m_writer.write<uint32_t>(fmt_size);
	m_writer.write<wave_format>(format);
	if (format.format_id != 1)
	{
		m_writer.write<uint16_t>(m_extention_size);
	}
	m_writer.write(data_chunk_name.data(), data_chunk_name.size());
	m_writer.write<uint32_t>(m_data_size);
}

void wave_writer::close()
{
	m_writer.seek(0, seek_origin::end);
	const uint16_t file_size = static_cast<uint16_t>(m_writer.tell() - 8);

	m_writer.seek(4, seek_origin::begin);
	m_writer.write<uint16_t>(file_size);
	m_writer.seek(38 + m_extention_size + 4, seek_origin::begin);
	m_writer.write<uint32_t>(m_data_size);
	m_writer.close();
}

bool wave_writer::write(const void* buffer, size_t size)
{
	m_data_size += static_cast<uint32_t>(size);
	m_writer.write(buffer, size);
	return true;
}

bool wave_writer::is_opened() const
{
	return m_writer.is_opened();
}