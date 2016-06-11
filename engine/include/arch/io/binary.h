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
#include <string>
#include "types.h"

namespace arch
{

///	<summary>
///	バイナリファイルを読み取ります。
///	</summary>
class binary_reader
{
public:
	///	<summary>
	///	コンストラクタ
	///	</summary>
	binary_reader();

	///	<summary>
	///	コンストラクタ
	///	</summary>
	binary_reader(const binary_reader& reader);

	///	<summary>
	///	コンストラクタ
	///	</summary>
	binary_reader(binary_reader&& reader);

	///	<summary>
	///	ファイルを開きます。
	///	</summary>
	binary_reader(const std::string& path);

	///	<summary>
	///	デストラクタ
	///	</summary>
	~binary_reader();

	///	<summary>
	///	ファイルを閉じます。
	///	</summary>
	void close();

	size_t size() const;
	bool read(void* buffer, size_t size) const;
	template<typename Type> Type read() const;
	template<typename Type> Type read(Type error_value) const;
	bool seek(long long distance, seek_origin origin = seek_origin::current) const;
	size_t tell() const;
	bool is_opened() const;
	bool eof() const;

	bool operator!() const;
	binary_reader& operator=(const binary_reader& reader);
	binary_reader& operator=(binary_reader&& reader);

private:
	class impl;
	std::shared_ptr<impl> pimpl;
};

template<typename Type> inline Type binary_reader::read() const
{
	Type value;
	read(&value, sizeof(Type));
	return value;
}

template<typename Type> inline Type binary_reader::read(Type error_value) const
{
	Type value;
	return read(&value, sizeof(Type)) ? value : error_value;
}


///	<summary>
///	バイナリファイルを読み取ります。
///	</summary>
class binary_writer
{
public:
	///	<summary>
	///	コンストラクタ
	///	</summary>
	binary_writer();

	///	<summary>
	///	コンストラクタ
	///	</summary>
	binary_writer(const binary_writer& writer);

	///	<summary>
	///	コンストラクタ
	///	</summary>
	binary_writer(binary_writer&& writer);

	///	<summary>
	///	ファイルを開きます。
	///	</summary>
	binary_writer(const std::string& path, open_mode mode = open_mode::append);

	///	<summary>
	///	デストラクタ
	///	</summary>
	~binary_writer();

	///	<summary>
	///	ファイルを閉じます。
	///	</summary>
	void close();

	void flush() const;
	bool write(const void* buffer, size_t size) const;
	template<typename Type> long long write(const Type& value) const;
	bool seek(long long distance, seek_origin origin = seek_origin::current) const;
	size_t tell() const;
	bool is_opened() const;

	bool operator!() const;

	binary_writer& operator=(const binary_writer& writer);
	binary_writer& operator=(binary_writer&& writer);

private:
	class impl;
	std::shared_ptr<impl> pimpl;
};

template<typename Type> inline long long binary_writer::write(const Type& value) const
{
	return write(&value, sizeof(Type));
}

}