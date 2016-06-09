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

/*!
*	@brief 4元数(クォータニオン)を表します。
*/
template <typename value_type>
class quaternion
{
public:
	quaternion() = default;
	~quaternion() = default;

	constexpr quaternion(value_type pitch, value_type yaw, value_type roll)
		: quaternion(vector3<value_type>(pitch, yaw, roll))
	{
	}

	constexpr quaternion(value_type _x, value_type _y, value_type _z, value_type _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	quaternion(const vector3<value_type>& angles)
	{
		vector3<value_type>	half_angles;
		vector3<value_type>	sin_angles, cos_angles;
		vector4<value_type> q0, q1;

		half_angles = vector3<value_type>(angles.x, angles.y, angles.z) * static_cast<value_type>(0.5);
		sin_angles.x = sin(half_angles.x);
		sin_angles.y = sin(half_angles.y);
		sin_angles.z = sin(half_angles.z);
		cos_angles.x = cos(half_angles.x);
		cos_angles.y = cos(half_angles.y);
		cos_angles.z = cos(half_angles.z);

		q0.x = sin_angles.x * cos_angles.y * cos_angles.z;
		q0.y = cos_angles.x * sin_angles.y * cos_angles.z;
		q0.z = cos_angles.x * cos_angles.y * sin_angles.z;
		q0.w = cos_angles.x * cos_angles.y * cos_angles.z;

		q1.x = cos_angles.x * sin_angles.y * sin_angles.z;
		q1.y = -sin_angles.x * cos_angles.y * sin_angles.z;
		q1.z = -sin_angles.x * sin_angles.y * cos_angles.z;
		q1.w = sin_angles.x * sin_angles.y * sin_angles.z;

		*this = q0 + q1;
	}

	quaternion(const vector3<value_type>& axis, value_type angle)
	{
		angle *= static_cast<value_type>(0.5);

		value_type sin_angle = sin(angle);
		vector3<value_type> norm_axis = axis.normalized();

		x = sin_angle * norm_axis.x;
		y = sin_angle * norm_axis.y;
		z = sin_angle * norm_axis.z;
		w = cos(angle);
	}

	quaternion(const vector4<value_type>& _q)
		: x(_q.x), y(_q.y), z(_q.z), w(_q.w)
	{
	}

	quaternion& conjugate()
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}
	
	constexpr quaternion conjugated() const
	{
		return quaternion(-x, -y, -z, w);
	}

	vector3<value_type> rotate(const vector3<value_type>& _vector) const
	{
		quaternion<value_type> vec(_vector.x, _vector.y, _vector.z, static_cast<value_type>(0.0));
		return ((conjugated() * vec) * (*this)).real;
	}

	vector4<value_type> rotate(const vector4<value_type>& _vector) const
	{
		quaternion<value_type> vec(_vector.x, _vector.y, _vector.z, static_cast<value_type>(0.0));
		auto result = (conjugated() * vec) * (*this);
	}

public:
	quaternion& operator=(const quaternion& quaternion)
	{
		x = quaternion.x;
		y = quaternion.y;
		z = quaternion.z;
		w = quaternion.w;
		return *this;
	}

	quaternion& operator=(const vector3<value_type>& angles)
	{
		*this = quaternion(angles);
		return *this;
	}

	quaternion operator*(const quaternion& _quaternion) const
	{

		return quaternion
			(
				(this->w * _quaternion.x) + (this->x * _quaternion.w) + (this->y * _quaternion.z) - (this->z * _quaternion.y),
				(this->w * _quaternion.y) - (this->x * _quaternion.z) + (this->y * _quaternion.w) + (this->z * _quaternion.x),
				(this->w * _quaternion.z) + (this->x * _quaternion.y) - (this->y * _quaternion.x) + (this->z * _quaternion.w),
				(this->w * _quaternion.w) - (this->x * _quaternion.x) - (this->y * _quaternion.y) - (this->z * _quaternion.z)
				);
	}

	quaternion& operator*=(const quaternion& quaternion)
	{
		*this = *this * quaternion;
		return *this;
	}

	bool operator==(const quaternion& quaternion) const
	{
		return (x == quaternion.x && y == quaternion.y && z == quaternion.z && w == quaternion.w);
	}

	bool operator!=(const quaternion& quaternion) const
	{
		return (x != quaternion.x || y != quaternion.y || z != quaternion.z || w != quaternion.w);
	}

public:
	static constexpr quaternion& identity()
	{
		return quaternion(static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(1.0));
	}


public:
	union
	{
		struct
		{
			value_type x;
			value_type y;
			value_type z;
			value_type w;
		};
		struct
		{
			vector3<value_type> real;
			value_type complex;
		};
		vector4<value_type> vec4;
		value_type data[4];
	};
};

}
