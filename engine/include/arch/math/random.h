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

#include <random>
#include <limits>
#include <type_traits>

namespace arch
{

inline std::mt19937_64& get_default_random_engine()
{
	static std::mt19937_64 default_random_engine;
	return default_random_engine;
}

inline double random()
{
	return std::uniform_real_distribution<double>(0.0, 1.0)(get_default_random_engine());
}

template<class value_type> inline value_type random()
{
	return random(std::numeric_limits<value_type>::min(), std::numeric_limits<value_type>::max());
}

template<class value_type> inline value_type random(value_type _minimum, value_type _maximum)
{
	return std::conditional<std::is_integral<value_type>::value, std::uniform_int_distribution<value_type>, std::uniform_real_distribution<value_type>>::type(_minimum, _maximum)(get_default_random_engine());
}

}