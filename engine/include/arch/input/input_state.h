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

#include <cstdint>

namespace arch
{

struct input_state final
{
	int32_t identity;	///
	bool pressed;		/// キーが押されている
	bool released;		/// キーが離された
	bool clicked;		/// キーが押された
};

}