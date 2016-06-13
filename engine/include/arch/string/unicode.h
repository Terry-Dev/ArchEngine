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

#include <string>

namespace arch
{

enum class text_encoding
{
	unspecified,
	ansi,
	utf8,
	utf16,
	utf32,
};

///	<summary>
///	UTF-8文字のコードポイントまでのサイズを取得します。
///	</summary>
inline constexpr size_t utf8_code_point_size(char c)
{
	return (c < 0x80) ? 1 : (c < 0xe0) ? 2 : (c < 0xf0) ? 3 : 4;
}

///	<summary>
///	UTF-16文字のコードポイントまでのサイズを取得します。
///	</summary>
inline constexpr size_t utf16_code_point_size(char16_t c)
{
	return (0xd800 <= c && c <= 0xdbff) ? 2 : 1;
}

}