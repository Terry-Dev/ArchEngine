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

#include <codecvt>
#include "unicode.h"

namespace arch
{

///	<summary>
///	ansi文字コードへの変換
///	</summary>
class codecvt_ansi
{
public:
	static std::string from_ansi(const std::string& _ansi);
	static std::string from_utf8(const std::string& _utf8);
	static std::string from_utf16le(const std::u16string& _utf16le);
	static std::string from_utf16be(const std::u16string& _utf16be);
	static std::string from_utf32le(const std::u32string& _utf32le);
	static std::string from_utf32be(const std::u32string& _utf32be);
};

///	<summary>
///	UTF-8文字コードへの変換
///	</summary>
class codecvt_utf8
{
public:
	static std::string from_ansi(const std::string& _ansi);
	static std::string from_utf8(const std::string& _utf8);
	static std::string from_utf16le(const std::u16string& _utf16le);
	static std::string from_utf16be(const std::u16string& _utf16be);
	static std::string from_utf32le(const std::u32string& _utf32le);
	static std::string from_utf32be(const std::u32string& _utf32be);
};

///	<summary>
///	UTF-16LE文字コードへの変換
///	</summary>
class codecvt_utf16le
{
public:
	static std::u16string from_ansi(const std::string& _ansi);
	static std::u16string from_utf8(const std::string& _utf8);
	static std::u16string from_utf16le(const std::u16string& _utf16le);
	static std::u16string from_utf16be(const std::u16string& _utf16be);
	static std::u16string from_utf32le(const std::u32string& _utf32le);
	static std::u16string from_utf32be(const std::u32string& _utf32be);
};

///	<summary>
///	UTF-16BE文字コードへの変換
///	</summary>
class codecvt_utf16be
{
public:
	static std::u16string from_ansi(const std::string& _ansi);
	static std::u16string from_utf8(const std::string& _utf8);
	static std::u16string from_utf16le(const std::u16string& _utf16le);
	static std::u16string from_utf16be(const std::u16string& _utf16be);
	static std::u16string from_utf32le(const std::u32string& _utf32le);
	static std::u16string from_utf32be(const std::u32string& _utf32be);
};
/*
///	<summary>
///	UTF-32LE文字コードへの変換
///	</summary>
class codecvt_utf32le
{
public:
	static std::u32string from_ansi(const std::string& _ansi);
	static std::u32string from_utf8(const std::string& _utf8);
	static std::u32string from_utf16le(const std::u16string& _utf16le);
	static std::u32string from_utf16be(const std::u16string& _utf16be);
	static std::u32string from_utf32le(const std::u32string& _utf32le);
	static std::u32string from_utf32be(const std::u32string& _utf32be);
};

///	<summary>
///	UTF-32BE文字コードへの変換
///	</summary>
class codecvt_utf32be
{
public:
	static std::u32string from_ansi(const std::string& _ansi);
	static std::u32string from_utf8(const std::string& _utf8);
	static std::u32string from_utf16le(const std::u16string& _utf16le);
	static std::u32string from_utf16be(const std::u16string& _utf16be);
	static std::u32string from_utf32le(const std::u32string& _utf32le);
	static std::u32string from_utf32be(const std::u32string& _utf32be);
};
*/
}