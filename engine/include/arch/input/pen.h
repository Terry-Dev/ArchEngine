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

/// <value>�M��(0�`1)</value>
static double pressure;

/// <value>���W�A���P�ʂ̐����p(0�`��/2)</value>
static double altitude;

/// <value>���W�A���P�ʂ̕��ʊp(0�`2��)</value>
static double azimuth;

};

}