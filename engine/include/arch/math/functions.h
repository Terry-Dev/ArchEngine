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

#include <cmath>
#include <type_traits>
#include "constants.h"

namespace arch
{

template<class type> inline constexpr type round(type _value)
{
	return std::floor(_value + static_cast<type>(0.5));
}

template<class type> inline constexpr type min(type _a, type _b)
{
	return _a < _b ? _a : _b;
}

template<class type, class... args> inline constexpr type min(type _first, args... _value)
{
	return min(_first, min(_value...));
}

template<class type> inline constexpr type max(type _a, type _b)
{
	return _a > _b ? _a : _b;
}

template<class type, class... args> inline constexpr type max(type _first, args... _value)
{
	return max(_first, max(_value...));
}

template<class type> inline constexpr type clamp(type value, type minimum, type maximum)
{
	return min(max(value, minimum), maximum);
}

template<class type> inline constexpr bool all(type _value)
{
	return _value != static_cast<type>(0.0);
}

template<class type, class... args> inline constexpr bool all(type _first, args... _value)
{
	return all(_first) && all(_value...);
}

template<class type> inline constexpr bool any(type _value)
{
	return _value != static_cast<type>(0.0);
}

template<class type, class... args> inline constexpr bool any(type _first, args... _value)
{
	return any(_first) || any(_value...);
}

/*!
*	@brief 0��菬�����ꍇ��-1�A1���傫���ꍇ��1�A0�̏ꍇ��0��Ԃ��܂��B
*/
template<class type> inline constexpr type sign(type _value)
{
	return (_value < static_cast<type>(0.0)) ? static_cast<type>(-1.0) : (_value > static_cast<type>(0.0)) ? static_cast<type>(1.0) : static_cast<type>(0.0);
}


/*!
*	@brief �ʓx��x���ɕϊ����܂��B
*	@param [in]	Radians	�ʓx
*	@return �x��
*/
template<class type> inline constexpr type degrees(type radians)
{
	return static_cast<type>(180.0) / constant::pi<type>() * radians;
}

/*!
*	@brief �x�����ʓx�ɕϊ����܂��B
*	@param [in]	Degrees	�x��
*	@return �ʓx
*/
template<class type> inline constexpr type radians(type degrees)
{
	return constant::pi<type>() / static_cast<type>(180.0) * degrees;
}

/*!
*	@brief �ő����
*/
template<class type> inline constexpr type greatest_common_divisor(type a, type b)
{
	static_assert(std::is_integral<type>::value, "This type must be an integral type.");
	type h = max(a, b);
	type l = min(a, b);
	while(l != static_cast<type>(0))
	{
		type t = h % l;
		h = l;
		l = t;
	}
	return h;
}

/*!
*	@brief �ŏ����{��
*/
template<class type> inline constexpr type least_common_multiple(type a, type b)
{
	static_assert(std::is_integral<type>::value, "This type must be an integral type.");
	return a * b / greatest_common_divisor(a, b);
}

template<class type> inline constexpr type factorial(type n)
{
	static_assert(std::is_integral<type>::value, "This type must be an integral type.");
	return n != static_cast<type>(0) ? n * factorial(n - static_cast<type>(1)) : static_cast<type>(1);
}

template<class type> inline constexpr type permutation(type n, type r)
{
	static_assert(std::is_integral<type>::value, "This type must be an integral type.");
	return factorial(n) / factorial(n - r);
}

template<class type> inline constexpr type combination(type n, type r)
{
	static_assert(std::is_integral<type>::value, "This type must be an integral type.");
	return permutation(n, r) / factorial(r);
}

template <typename type> inline constexpr type nearest_neighbor(const type& begin, const type& end, double factor)
{
	return factor <= 0.5 ? begin : end;
}

}
