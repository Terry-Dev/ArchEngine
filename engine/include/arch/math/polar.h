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

#include "vector.h"

namespace arch
{
	
template <typename type>
class polar2
{
public:
	typedef type value_type;
	typedef size_t size_type;
	typedef type* pointer;
	typedef const type* const_pointer;
	typedef type& reference;
	typedef const type& const_reference;

public:
	polar2() = default;
	constexpr polar2(value_type _radius, value_type _theta)
		: radius(_radius), theta(_theta)
	{
	}

	constexpr polar2(const polar2& _polar) noexcept
		: radius(_polar.radius), theta(_polar.theta)
	{
	}

	polar2& operator=(const polar2& _polar)
	{
		radius = _polar.radius;
		theta = _polar.theta;
		return *this;
	}

	constexpr bool operator==(const polar2& _polar) const
	{
		return radius == _polar.radius && theta == _polar.theta;
	}

	constexpr bool operator!=(const polar2& _polar) const
	{
		return radius != _polar.radius || theta != _polar.theta;
	}

	constexpr operator vector2<value_type>() const
	{
		return vector2<value_type>(sin(theta) * radius, cos(theta) * radius);
	}

public:
	value_type radius;
	value_type theta;
};

template <typename type>
class polar3
{
public:
	typedef type value_type;
	typedef size_t size_type;
	typedef type* pointer;
	typedef const type* const_pointer;
	typedef type& reference;
	typedef const type& const_reference;

public:
	polar3() = default;
	constexpr polar3(value_type _radius, value_type _theta1, value_type _theta2)
		: radius(_radius), theta1(_theta1), theta2(_theta2)
	{
	}

	constexpr polar3(const polar3& _polar)
		: radius(_polar.radius), theta1(_polar.theta1), theta2(_polar.theta2)
	{
	}

	polar3& operator=(const polar3& _polar)
	{
		radius = _polar.radius;
		theta1 = _polar.theta1;
		theta2 = _polar.theta2;
		return *this;
	}

	constexpr bool operator==(const polar3& _polar) const
	{
		return radius == _polar.radius && theta1 == _polar.theta1 && theta2 == _polar.theta2;
	}

	constexpr bool operator!=(const polar3& polar) const
	{
		return radius != polar.radius || theta1 != polar.theta1 || theta2 != polar.theta2;
	}

	constexpr operator vector3<value_type>() const
	{
		value_type theta1_sin = sin(theta1);
		return vector3<value_type>(theta1_sin * cos(theta2) * radius, theta1_sin * sin(theta2) * radius, cos(theta1) * radius);
	}

public:
	value_type radius;
	value_type theta1;
	value_type theta2;
};

}
