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

#include <arch/math.h>
#include "input_state.h"

namespace arch
{

struct mouse final
{
	static input_state left;		///< 左ボタン
	static input_state right;		///< 右ボタン
	static input_state middle;		///< 中央ボタン
	static input_state button1;		///< ボタン 1
	static input_state button2;		///< ボタン 2
	static input_state button3;		///< ボタン 3
	static input_state button4;		///< ボタン 4
	static input_state button5;		///< ボタン 5
	static input_state button6;		///< ボタン 6
	static input_state button7;		///< ボタン 7
	static input_state button8;		///< ボタン 8

	static int2 position;
	static int3 move;
};

}