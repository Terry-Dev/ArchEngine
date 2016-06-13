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

#include <fstream>
#include <arch/io/binary.h>

using namespace arch;

class binary_reader::impl
{
public:
	std::ifstream stream;
};


binary_reader::binary_reader()
: pimpl(std::make_shared<impl>())
{
}

binary_reader::binary_reader(const binary_reader& reader)
: pimpl(reader.pimpl)
{
}

binary_reader::binary_reader(binary_reader&& reader)
: pimpl(std::move(reader.pimpl))
{
}

binary_reader::binary_reader(const std::string& path)
: pimpl(std::make_shared<impl>())
{
	pimpl->stream = std::ifstream(path, std::ios::in | std::ios::binary);
}

binary_reader::~binary_reader()
{
}

void binary_reader::close()
{
	pimpl->stream.close();
}

size_t binary_reader::size() const
{
	auto pos = pimpl->stream.tellg();
	auto size = pimpl->stream.seekg(0, std::ios::end).tellg();
	pimpl->stream.seekg(pos, std::ios::beg);
	return static_cast<size_t>(size);
}

bool binary_reader::read(void* buffer, size_t size) const
{
	return pimpl->stream.read(reinterpret_cast<char*>(buffer), size).good();
}

bool binary_reader::seek(long long distance, seek_origin origin) const
{
	static const std::ios::seekdir seek_origin_table[] =
	{
		std::ios::beg,
		std::ios::cur,
		std::ios::end,
	};
	return pimpl->stream.seekg(distance, seek_origin_table[static_cast<int>(origin)]).good();
}

size_t binary_reader::tell() const
{
	return static_cast<size_t>(pimpl->stream.tellg());
}

bool binary_reader::is_opened() const
{
	return pimpl->stream.is_open();
}

bool binary_reader::eof() const
{
	return pimpl->stream.eof();
}

bool binary_reader::operator!() const
{
	return !pimpl->stream;
}

binary_reader& binary_reader::operator=(const binary_reader& reader)
{
	pimpl = reader.pimpl;
	return *this;
}

binary_reader& binary_reader::operator=(binary_reader&& reader)
{
	pimpl = std::move(reader.pimpl);
	return *this;
}


class binary_writer::impl
{
public:
	std::ofstream stream;
};

binary_writer::binary_writer()
: pimpl(std::make_shared<impl>())
{
}

binary_writer::binary_writer(const binary_writer& writer)
: pimpl(writer.pimpl)
{
}

binary_writer::binary_writer(binary_writer&& writer)
: pimpl(std::move(writer.pimpl))
{
}

binary_writer::binary_writer(const std::string& path, open_mode mode)
: pimpl(std::make_shared<impl>())
{
	static const int open_flag_table[] =
	{
		std::ios::out | std::ios::binary | std::ios::app,	// append
		std::ios::out | std::ios::binary | std::ios::trunc,	// truncate
	};

	pimpl->stream = std::ofstream(path, open_flag_table[static_cast<int>(mode)]);
}

binary_writer::~binary_writer()
{
}

void binary_writer::close()
{
	pimpl->stream.close();
}

void binary_writer::flush() const
{
	pimpl->stream.flush();
}

bool binary_writer::write(const void* buffer, size_t size) const
{
	return pimpl->stream.write(reinterpret_cast<const char*>(buffer), size).good();
}

bool binary_writer::seek(long long distance, seek_origin origin) const
{
	static const std::ios::seekdir seek_origin_table[] =
	{
		std::ios::beg,
		std::ios::cur,
		std::ios::end,
	};
	return pimpl->stream.seekp(distance, seek_origin_table[static_cast<int>(origin)]).good();
}

size_t binary_writer::tell() const
{
	return static_cast<size_t>(pimpl->stream.tellp());
}

bool binary_writer::is_opened() const
{
	return pimpl->stream.is_open();
}

bool binary_writer::operator!() const
{
	return !pimpl->stream;
}

binary_writer& binary_writer::operator=(const binary_writer& writer)
{
	pimpl = writer.pimpl;
	return *this;
}

binary_writer& binary_writer::operator=(binary_writer&& writer)
{
	pimpl = std::move(writer.pimpl);
	return *this;
}
