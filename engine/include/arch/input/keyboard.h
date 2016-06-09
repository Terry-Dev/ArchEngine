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

#include <array>
#include "input_state.h"

namespace arch
{

struct keyboard final
{
	static input_state key_A;	///< A
	static input_state key_B;	///< B
	static input_state key_C;	///< C
	static input_state key_D;	///< D
	static input_state key_E;	///< E
	static input_state key_F;	///< F
	static input_state key_G;	///< G
	static input_state key_H;	///< H
	static input_state key_I;	///< I
	static input_state key_J;	///< J
	static input_state key_K;	///< K
	static input_state key_L;	///< L
	static input_state key_M;	///< M
	static input_state key_N;	///< N
	static input_state key_O;	///< O
	static input_state key_P;	///< P
	static input_state key_Q;	///< Q
	static input_state key_R;	///< R
	static input_state key_S;	///< S
	static input_state key_T;	///< T
	static input_state key_U;	///< U
	static input_state key_V;	///< V
	static input_state key_W;	///< W
	static input_state key_X;	///< X
	static input_state key_Y;	///< Y
	static input_state key_Z;	///< Z

	static input_state key_0;	///< 0
	static input_state key_1;	///< 1
	static input_state key_2;	///< 2
	static input_state key_3;	///< 3
	static input_state key_4;	///< 4
	static input_state key_5;	///< 5
	static input_state key_6;	///< 6
	static input_state key_7;	///< 7
	static input_state key_8;	///< 8
	static input_state key_9;	///< 9

	static input_state key_f1;	///< F1
	static input_state key_f2;	///< F2
	static input_state key_f3;	///< F3
	static input_state key_f4;	///< F4
	static input_state key_f5;	///< F5
	static input_state key_f6;	///< F6
	static input_state key_f7;	///< F7
	static input_state key_f8;	///< F8
	static input_state key_f9;	///< F9
	static input_state key_f10;	///< F10
	static input_state key_f11;	///< F11
	static input_state key_f12;	///< F12

	static input_state key_num_0;		///< テンキーの0
	static input_state key_num_1;		///< テンキーの1
	static input_state key_num_2;		///< テンキーの2
	static input_state key_num_3;		///< テンキーの3
	static input_state key_num_4;		///< テンキーの4
	static input_state key_num_5;		///< テンキーの5
	static input_state key_num_6;		///< テンキーの6
	static input_state key_num_7;		///< テンキーの7
	static input_state key_num_8;		///< テンキーの8
	static input_state key_num_9;		///< テンキーの9

	static input_state key_num_period;		///< テンキーの.
	static input_state key_num_divide;		///< テンキーの/
	static input_state key_num_multiply;	///< テンキーの*
	static input_state key_num_plus;		///< テンキーの+
	static input_state key_num_minus;		///< テンキーの-
	static input_state key_num_enter;		///< テンキーのEnter

	static input_state key_escape;	///< Esc

	static input_state key_up;		///< 上
	static input_state key_down;	///< 下
	static input_state key_left;	///< 左
	static input_state key_right;	///< 右

	static input_state key_minus;		///< -
	static input_state key_equals;		///< =
	static input_state key_tab;			///< Tab
	static input_state key_semicolon;	///< ;
	static input_state key_apostrophe;	///< '
	static input_state key_back_quote;	///< `

	static input_state key_enter;			///< Enter
	static input_state key_backspace;		///< BackSpace
	static input_state key_space;			///< Space

	static input_state key_left_bracket;	///< [
	static input_state key_right_bracket;	///< ]
	static input_state key_left_control;	///< 左Ctrl
	static input_state key_right_control;	///< 右Ctrl
	static input_state key_left_shift;		///< 左Shift
	static input_state key_right_shift;		///< 右Shift
	static input_state key_left_alt;		///< 左Alt
	static input_state key_right_alt;		///< 右Alt

	static input_state key_slash;			///< /
	static input_state key_backslash;		///< ＼

	static input_state key_comma;			///< ,
	static input_state key_period;			///< .
};

}