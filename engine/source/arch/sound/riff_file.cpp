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

#include "arch/math_function.h"
#include "arch/riff_file.h"

using namespace arch;

riff_reader::riff_reader()
: m_chunk_position(0), m_chunk_size(0), m_data_position(0)
{
	m_form_type.resize(4);
	m_chunk_name.resize(4);
}

riff_reader::riff_reader(const std::string& path)
: riff_reader()
{
	m_reader = binary_reader(path);
	if (!m_reader)
	{
		return;
	}

	m_reader.read(&m_chunk_name[0], m_chunk_name.size());
	if (m_chunk_name != "RIFF")
	{
		m_reader.close();
		return;
	}
	m_riff_size = m_reader.read<uint32_t>();
	m_reader.read(&m_form_type[0], m_form_type.size());
	m_reader.read(&m_chunk_name[0], m_chunk_name.size());
	m_chunk_size = m_reader.read<uint32_t>();
	m_chunk_position = m_reader.tell();
}

void riff_reader::close()
{
	m_reader.close();
}

size_t riff_reader::read(void* buffer, size_t size)
{
	if (m_data_position + size > m_chunk_size)
	{
		size = m_chunk_size - m_data_position;
	}
	m_data_position += size;
	return m_reader.read(buffer, size) ? size : 0;
}

bool riff_reader::seek(const std::string& chunk)
{
	m_reader.seek(12, seek_origin::begin);
	m_data_position = 0;
	while (!m_reader.eof())
	{
		m_reader.read(&m_chunk_name[0], m_chunk_name.size());
		m_chunk_size = m_reader.read<uint32_t>();
		if (m_chunk_name == chunk)
		{
			m_chunk_position = m_reader.tell();
			return true;
		}
		m_reader.seek(static_cast<long long>(m_chunk_size), seek_origin::current);
	}
	return false;
}

bool riff_reader::seek(size_t size)
{
	m_data_position = min(size, static_cast<size_t>(m_chunk_size));
	return m_reader.seek(static_cast<long long>(m_data_position + m_chunk_position), seek_origin::begin);
}

size_t riff_reader::tell() const
{
	return m_data_position;
}

const std::string& riff_reader::form_type() const
{
	return m_form_type;
}

const std::string& riff_reader::chunk() const
{
	return m_chunk_name;
}

uint32_t riff_reader::size() const
{
	return m_chunk_size;
}

bool riff_reader::is_opened() const
{
	return m_reader.is_opened();
}

bool riff_reader::end() const
{
	return m_data_position >= m_chunk_size;
}

bool riff_reader::operator!() const
{
	return !m_reader;
}

/*
riff_writer::riff_writer()
: m_chunk_position(0), m_chunk_size(0), m_data_position(0)
{
	m_chunk_name.resize(4);
}

riff_writer::riff_writer(const std::string& path)
: riff_writer()
{
	m_writer = binary_writer(path);
	if (!m_writer)
	{
		return;
	}
}

void riff_writer::close()
{
	m_writer.close();
}

bool riff_writer::write(const void* buffer, size_t size)
{
	m_data_size += size;
	m_writer.write(buffer, size);
	return true;
}

bool riff_writer::seek(const std::string& chunk)
{
	m_writer.seek(0, seek_origin::begin);
	m_data_position = 0;
	while (m_writer.e())
	{
		m_reader.read(&m_chunk_name[0], m_chunk_name.size());
		m_chunk_size = m_reader.read<uint32_t>();
		if (m_chunk_name == chunk)
		{
			m_chunk_position = m_reader.tell();
			return true;
		}
		m_reader.seek(static_cast<long long>(m_chunk_size), seek_origin::current);
	}
	return false;
}

bool riff_writer::seek(size_t size)
{
	m_data_position = min(size, static_cast<size_t>(m_chunk_size));
	return m_reader.seek(static_cast<long long>(m_data_position + m_chunk_position), seek_origin::begin);
}

bool riff_writer::is_opened() const
{
	return m_writer.is_opened();
}
*/