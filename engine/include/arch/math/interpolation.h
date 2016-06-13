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

namespace arch
{
	
template <typename type> inline constexpr type linear(const type& begin, const type& end, class type::value_type factor)
{
	return begin + (end - begin) * factor;
}

template <typename type> inline constexpr type hermite(const type& begin, const type& begin_velocity, const type& end, const type& end_velocity, class type::value_type factor)
{
	class type::value_type factor2 = factor * factor;
	class type::value_type factor3 = factor2 * factor;
	type a = 2.0 * begin + begin_velocity - 2.0 * end + end_velocity;
	type b = -3.0 * begin - 2.0 * begin_velocity + 3.0 * end - end_velocity;
	return a * factor3 + b * factor2 + begin_velocity * factor + begin;
}

}