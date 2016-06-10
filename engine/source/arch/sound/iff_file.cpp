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

#include "arch/iff_file.h"
#include "arch/endian.h"
#include "arch/math_function.h"

using namespace arch;

iff_reader::iff_reader()
: m_chunk_position(0), m_chunk_size(0), m_data_position(0)
{
	m_form_type.resize(4);
	m_chunk_name.resize(4);
}

iff_reader::iff_reader(const std::string& path)
: iff_reader()
{
	m_reader = binary_reader(path);
	if (!m_reader)
	{
		return;
	}

	m_reader.read(&m_chunk_name[0], m_chunk_name.size());
	if (m_chunk_name != "FORM" && m_chunk_name != "LIST" && m_chunk_name != "CAT ")
	{
		m_reader.close();
		return;
	}
	m_iff_size = endian::swap(m_reader.read<uint32_t>());
	m_reader.read(&m_form_type[0], m_form_type.size());
	m_reader.read(&m_chunk_name[0], m_chunk_name.size());
	m_chunk_size = endian::swap(m_reader.read<uint32_t>());
	m_chunk_position = m_reader.tell();
}

void iff_reader::close()
{
	m_reader.close();
}

size_t iff_reader::read(void* buffer, size_t size)
{
	if (m_data_position + size > m_chunk_size)
	{
		size = m_chunk_size - m_data_position;
	}
	m_data_position += size;
	return m_reader.read(buffer, size) ? size : 0;
}

bool iff_reader::seek(const std::string& chunk)
{
	m_reader.seek(12, seek_origin::begin);
	m_data_position = 0;
	while (!m_reader.eof())
	{
		m_reader.read(&m_chunk_name[0], m_chunk_name.size());
		m_chunk_size = endian::swap(m_reader.read<uint32_t>());
		if (m_chunk_name == chunk)
		{
			m_chunk_position = m_reader.tell();
			return true;
		}
		m_reader.seek(static_cast<long long>(m_chunk_size), seek_origin::current);
	}
	return false;
}

bool iff_reader::seek(size_t size)
{
	m_data_position = min(size, static_cast<size_t>(m_chunk_size));
	return m_reader.seek(static_cast<long long>(m_data_position + m_chunk_position), seek_origin::begin);
}

size_t iff_reader::tell() const
{
	return m_data_position;
}

const std::string& iff_reader::form_type() const
{
	return m_form_type;
}

const std::string& iff_reader::chunk() const
{
	return m_chunk_name;
}

uint32_t iff_reader::size() const
{
	return m_chunk_size;
}

bool iff_reader::is_opened() const
{
	return m_reader.is_opened();
}

bool iff_reader::end() const
{
	return m_data_position >= m_chunk_size;
}

bool iff_reader::operator!() const
{
	return !m_reader;
}