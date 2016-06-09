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

	static input_state key_num_0;		///< �e���L�[��0
	static input_state key_num_1;		///< �e���L�[��1
	static input_state key_num_2;		///< �e���L�[��2
	static input_state key_num_3;		///< �e���L�[��3
	static input_state key_num_4;		///< �e���L�[��4
	static input_state key_num_5;		///< �e���L�[��5
	static input_state key_num_6;		///< �e���L�[��6
	static input_state key_num_7;		///< �e���L�[��7
	static input_state key_num_8;		///< �e���L�[��8
	static input_state key_num_9;		///< �e���L�[��9

	static input_state key_num_period;		///< �e���L�[��.
	static input_state key_num_divide;		///< �e���L�[��/
	static input_state key_num_multiply;	///< �e���L�[��*
	static input_state key_num_plus;		///< �e���L�[��+
	static input_state key_num_minus;		///< �e���L�[��-
	static input_state key_num_enter;		///< �e���L�[��Enter

	static input_state key_escape;	///< Esc

	static input_state key_up;		///< ��
	static input_state key_down;	///< ��
	static input_state key_left;	///< ��
	static input_state key_right;	///< �E

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
	static input_state key_left_control;	///< ��Ctrl
	static input_state key_right_control;	///< �ECtrl
	static input_state key_left_shift;		///< ��Shift
	static input_state key_right_shift;		///< �EShift
	static input_state key_left_alt;		///< ��Alt
	static input_state key_right_alt;		///< �EAlt

	static input_state key_slash;			///< /
	static input_state key_backslash;		///< �_

	static input_state key_comma;			///< ,
	static input_state key_period;			///< .
};

}