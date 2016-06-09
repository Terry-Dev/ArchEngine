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

#include "input_state.h"

namespace arch
{

struct pen final
{

static bool supports;
static bool supports_pressure;
static bool supports_tilt;
static bool is_eraser;

/// <value>•Mˆ³(0`1)</value>
static double pressure;

/// <value>ƒ‰ƒWƒAƒ“’PˆÊ‚Ì‚’¼Šp(0`ƒÎ/2)</value>
static double altitude;

/// <value>ƒ‰ƒWƒAƒ“’PˆÊ‚Ì•ûˆÊŠp(0`2ƒÎ)</value>
static double azimuth;

};

}