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

#include <vector>
#include <arch/math.h>
#include "input_state.h"

namespace arch
{

struct touch final
{

struct info final
{
	int			identity;	/// 識別ID
	int2		position;	/// 位置
	double2		move;		/// 移動量
	input_state	state;		/// 状態
};

static bool supports;
static bool supports_multi;
static std::vector<info> infos;

};

}