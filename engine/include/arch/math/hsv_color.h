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

#include <type_traits>
#include <limits>
#include "vector.h"
#include "interpolation.h"

namespace arch
{

/*!
*	@brief 色相、彩度、明度で色を表します。
*/
template<class type = double>
class hsv_color
{
public:
	static_assert(std::is_floating_point<type>::value, "This type must be an floating point type.");

	/*!
	*	@brief コンストラクタ
	*/
	hsv_color() = default;

	/*!
	*	@brief 色相、彩度、明度を設定します
	*	@param [in]	h	色相
	*	@param [in]	s	彩度
	*	@param [in]	v	明度
	*/
	hsv_color(type _h, type _s, type _v)
		: h(_h), s(_s), v(_v)
	{
	}

	/*!
	*	@brief 色で色相、彩度、明度を設定します
	*	@param [in]	Color	色
	*/
	hsv_color(const uchar4& c) noexcept
	{
		*this = c;
	}

	/*!
	*	@brief 色で色相、彩度、明度を設定します
	*	@param [in]	Color	色
	*/
	hsv_color(const vector4<type>& c) noexcept
	{
		*this = c;
	}

	/*!
	*	@brief デストラクタ
	*/
	~hsv_color() = default;

	template<class convert_type = double> vector4<convert_type> to_vector4() const
	{
		vector4<type> result;

		result.a = static_cast<type>(1.0);

		if (v <= static_cast<type>(0.0))
		{
			result.r = v;
			result.g = v;
			result.b = v;

			return static_cast<vector4<type>>(result);
		}

		int hi = static_cast<int>(floor(h / static_cast<type>(60.0))) % 6;
		type f = h / static_cast<type>(60.0) - static_cast<type>(hi);

		type p = v * (static_cast<type>(1.0) - s);
		type q = v * (static_cast<type>(1.0) - f * s);
		type t = v * (static_cast<type>(1.0) - (static_cast<type>(1.0f) - f) * s);

		switch (hi)
		{
		case 0: result.r = v;	result.g = t;	result.b = p;	break;
		case 1: result.r = q;	result.g = v;	result.b = p;	break;
		case 2: result.r = p;	result.g = v;	result.b = t;	break;
		case 3: result.r = p;	result.g = q;	result.b = v;	break;
		case 4: result.r = t;	result.g = p;	result.b = v;	break;
		case 5: result.r = v;	result.g = p;	result.b = q;	break;
		}

		if (std::is_integral<convert_type>::value)
		{
			result.r = linear(static_cast<type>(std::numeric_limits<convert_type>::min()), static_cast<type>(std::numeric_limits<convert_type>::max()), result.r);
			result.g = linear(static_cast<type>(std::numeric_limits<convert_type>::min()), static_cast<type>(std::numeric_limits<convert_type>::max()), result.g);
			result.b = linear(static_cast<type>(std::numeric_limits<convert_type>::min()), static_cast<type>(std::numeric_limits<convert_type>::max()), result.b);
			result.a = linear(static_cast<type>(std::numeric_limits<convert_type>::min()), static_cast<type>(std::numeric_limits<convert_type>::max()), result.a);
		}

		return static_cast<vector4<convert_type>>(result);
	}

	hsv_color& operator=(const hsv_color& c)
	{
		this->h = c.h;
		this->s = c.s;
		this->v = c.v;
		return *this;
	}

	hsv_color& operator=(const uchar4& c)
	{
		*this = static_cast<vector4<type>>(c) / static_cast<type>(255.0);
		return *this;
	}

	hsv_color& operator=(const vector4<type>& c)
	{
		type max = arch::max(arch::max(color.r, color.g), color.b);
		type min = arch::min(arch::min(color.r, color.g), color.b);
		type m = max - min;

		v = max;

		if (max == min)
		{
			h = static_cast<type>(0.0);
			s = static_cast<type>(0.0);

			return *this;
		}

		s = m / max;

		if (max == color.r)
		{
			h = static_cast<type>(60.0) * (color.g - color.b) / m;
		}
		else if (max == color.b)
		{
			h = static_cast<type>(60.0) * (static_cast<type>(2.0) + (color.b - color.r) / m);
		}
		else
		{
			h = static_cast<type>(60.0) * (static_cast<type>(4.0) + (color.r - color.g) / m);
		}

		if (h < static_cast<type>(0.0))
		{
			h += static_cast<type>(360.0);
		}

		return *this;
	}

public:
	type h;	///< 色相
	type s;	///< 彩度
	type v;	///< 明度
};

template<typename CharT, class type> inline std::basic_ostream<CharT>& operator <<(std::basic_ostream<CharT>& os, const hsv_color<type>& c)
{
	return os << '(' << c.h << ',' << c.s << ',' << c.v << ')';
}

template<typename CharT, class type> inline std::basic_istream<CharT>& operator >>(std::basic_istream<CharT>& is, hsv_color<type>& c)
{
	CharT dummy;
	return is >> dummy >> c.h >> dummy >> c.s >> dummy >> c.v >> dummy;
}

}