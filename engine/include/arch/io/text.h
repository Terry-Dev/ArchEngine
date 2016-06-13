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

#pragma once

#include <memory>
#include <arch/utility.h>
#include <arch/string.h>
#include "binary.h"

namespace arch
{

namespace text
{

///	<summary>
///	テキストファイルを読み取ります。
///	</summary>
class reader
{
public:
	///	<summary>
	///	コンストラクタ
	///	</summary>
	reader();

	///	<summary>
	///	コンストラクタ
	///	</summary>
	reader(const reader& _reader);

	///	<summary>
	///	コンストラクタ
	///	</summary>
	reader(reader&& _reader);

	///	<summary>
	///	ファイルを開きます。
	///	</summary>
	reader(const std::string& _path, text_encoding _encode = text_encoding::unspecified, endian_type _endian = endian_type::little_endian);

	///	<summary>
	///	デストラクタ
	///	</summary>
	~reader();

	///	<summary>
	///	ファイルを閉じます。
	///	</summary>
	void close();
	 
	bool read_char(std::string& _str, text_encoding _encode = text_encoding::unspecified) const;
	bool read_char(std::u16string& _str, endian_type _endian = endian_type::little_endian) const;
	//bool read_char(std::u32string& _str, endian::endian_type _endian = endian::little_endian) const;

	bool read_string(std::string& _str, size_t _count, text_encoding _encode = text_encoding::unspecified) const;
	bool read_string(std::u16string& _str, size_t _count, endian_type _endian = endian_type::little_endian) const;
	//bool read_string(std::u32string& _str, uint _count, endian::endian_type _endian = endian::little_endian) const;

	bool read_line(std::string& _str, text_encoding _encode = text_encoding::unspecified) const;
	bool read_line(std::u16string& _str, endian_type _endian = endian_type::little_endian) const;
	//bool read_line(std::u32string& _str, endian::endian_type _endian = endian::little_endian) const;

	bool read_contents(std::string& _str, text_encoding _encode = text_encoding::unspecified) const;
	bool read_contents(std::u16string& _str, endian_type _endian = endian_type::little_endian) const;
	//bool read_contents(std::u32string& _str, endian::endian_type _endian = endian::little_endian) const;
	
	bool is_opened() const;
	bool eof() const;

	bool operator!() const;

	reader& operator=(const reader& _reader);
	reader& operator=(reader&& _reader);

private:
	class impl;
	std::shared_ptr<impl> pimpl;
};


///	<summary>
///	テキストファイルを読み取ります。
///	</summary>
class writer
{
public:
	///	<summary>
	///	コンストラクタ
	///	</summary>
	writer();

	///	<summary>
	///	コンストラクタ
	///	</summary>
	writer(const writer& writer);

	///	<summary>
	///	コンストラクタ
	///	</summary>
	writer(writer&& writer);

	///	<summary>
	///	ファイルを開きます。
	///	</summary>
	writer(const std::string& _path, open_mode _mode = open_mode::truncate, text_encoding encode = text_encoding::unspecified, endian_type _endian = endian_type::little_endian);

	///	<summary>
	///	デストラクタ
	///	</summary>
	~writer();

	///	<summary>
	///	ファイルを閉じます。
	///	</summary>
	void close();

	void flush() const;

	void write(char c) const;
	void write(const std::string& string, text_encoding _encode = text_encoding::unspecified) const;
	void write(const std::u16string& string, endian_type _endian = endian_type::little_endian) const;
	//void write(const std::u32string& string, endian::endian_type _endian = endian::little_endian) const;

	void write_line(const std::string& string, text_encoding _encode = text_encoding::unspecified) const;
	void write_line(const std::u16string& string, endian_type _endian = endian_type::little_endian) const;
	//void write_line(const std::u32string& string, endian::endian_type _endian = endian::little_endian) const;

	bool is_opened() const;

	bool	operator!() const;

	writer& operator=(const writer& writer);
	writer& operator=(writer&& writer);

private:
	class impl;
	std::shared_ptr<impl> pimpl;
};

}

}