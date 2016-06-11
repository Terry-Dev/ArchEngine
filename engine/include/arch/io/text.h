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
#include "unicode.h"
#include "endian.h"
#include "binary_file.h"

namespace arch
{

///	<summary>
///	テキストファイルを読み取ります。
///	</summary>
class text_reader
{
public:
	///	<summary>
	///	コンストラクタ
	///	</summary>
	text_reader();

	///	<summary>
	///	コンストラクタ
	///	</summary>
	text_reader(const text_reader& _reader);

	///	<summary>
	///	コンストラクタ
	///	</summary>
	text_reader(text_reader&& _reader);

	///	<summary>
	///	ファイルを開きます。
	///	</summary>
	text_reader(const std::string& _path, text_encoding _encode = text_encoding::unspecified, endian::endian_type _endian = endian::little_endian);

	///	<summary>
	///	デストラクタ
	///	</summary>
	~text_reader();

	///	<summary>
	///	ファイルを閉じます。
	///	</summary>
	void close();
	 
	bool read_char(std::string& _str, text_encoding _encode = text_encoding::unspecified) const;
	bool read_char(std::u16string& _str, endian::endian_type _endian = endian::little_endian) const;
	//bool read_char(std::u32string& _str, endian::endian_type _endian = endian::little_endian) const;

	bool read_string(std::string& _str, uint _count, text_encoding _encode = text_encoding::unspecified) const;
	bool read_string(std::u16string& _str, uint _count, endian::endian_type _endian = endian::little_endian) const;
	//bool read_string(std::u32string& _str, uint _count, endian::endian_type _endian = endian::little_endian) const;

	bool read_line(std::string& _str, text_encoding _encode = text_encoding::unspecified) const;
	bool read_line(std::u16string& _str, endian::endian_type _endian = endian::little_endian) const;
	//bool read_line(std::u32string& _str, endian::endian_type _endian = endian::little_endian) const;

	bool read_contents(std::string& _str, text_encoding _encode = text_encoding::unspecified) const;
	bool read_contents(std::u16string& _str, endian::endian_type _endian = endian::little_endian) const;
	//bool read_contents(std::u32string& _str, endian::endian_type _endian = endian::little_endian) const;
	
	bool is_opened() const;
	bool eof() const;

	bool operator!() const;

	text_reader& operator=(const text_reader& _reader);
	text_reader& operator=(text_reader&& _reader);

private:
	class impl;
	std::shared_ptr<impl> pimpl;
};


///	<summary>
///	テキストファイルを読み取ります。
///	</summary>
class text_writer
{
public:
	///	<summary>
	///	コンストラクタ
	///	</summary>
	text_writer();

	///	<summary>
	///	コンストラクタ
	///	</summary>
	text_writer(const text_writer& writer);

	///	<summary>
	///	コンストラクタ
	///	</summary>
	text_writer(text_writer&& writer);

	///	<summary>
	///	ファイルを開きます。
	///	</summary>
	text_writer(const std::string& _path, open_mode _mode = open_mode::truncate, text_encoding encode = text_encoding::unspecified, endian::endian_type _endian = endian::little_endian);

	///	<summary>
	///	デストラクタ
	///	</summary>
	~text_writer();

	///	<summary>
	///	ファイルを閉じます。
	///	</summary>
	void close();

	void flush() const;

	void write(char c) const;
	void write(const std::string& string, text_encoding _encode = text_encoding::unspecified) const;
	void write(const std::u16string& string, endian::endian_type _endian = endian::little_endian) const;
	//void write(const std::u32string& string, endian::endian_type _endian = endian::little_endian) const;

	void write_line(const std::string& string, text_encoding _encode = text_encoding::unspecified) const;
	void write_line(const std::u16string& string, endian::endian_type _endian = endian::little_endian) const;
	//void write_line(const std::u32string& string, endian::endian_type _endian = endian::little_endian) const;

	bool is_opened() const;

	bool	operator!() const;

	text_writer& operator=(const text_writer& writer);
	text_writer& operator=(text_writer&& writer);

private:
	class impl;
	std::shared_ptr<impl> pimpl;
};

}