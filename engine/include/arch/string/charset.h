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
#include <locale>

namespace arch
{

namespace charset
{

///	<summary>
///	ワイド文字列をマルチバイト文字列に変換します。
///	</summary>
std::string narrow(const std::wstring& _widen);

///	<summary>
///	マルチバイト文字列をワイド文字列に変換します。
///	</summary>
std::wstring widen(const std::string& _narrow);

}

}