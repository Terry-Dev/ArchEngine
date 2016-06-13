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

enum class endian_type
{
	little_endian,
	big_endian,
};

template<typename value_type> value_type endian_swap(value_type value)
{
	uint8_t* p = reinterpret_cast<uint8_t*>(&value);
	value_type swapped_value = 0;
	for (int i = 0; i < sizeof(value_type); i++)
	{
		swapped_value |= p[i] << (8 * (sizeof(value_type) - i - 1));
	}
	return swapped_value;
}

}