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

#include <iostream>
#include "scalar.h"
#include "random.h"
#include "functions.h"

namespace arch
{
	
template <typename type> class vector2;
template <typename type> class vector3;
template <typename type> class vector4;

typedef vector2<char>	char2;
typedef vector2<uchar>	uchar2;
typedef vector2<short>	short2;
typedef vector2<ushort>	ushort2;
typedef vector2<int>	int2;
typedef vector2<uint>	uint2;
typedef vector2<long>	long2;
typedef vector2<ulong>	ulong2;
typedef vector2<float>	float2;
typedef vector2<double>	double2;

typedef vector3<char>	char3;
typedef vector3<uchar>	uchar3;
typedef vector3<short>	short3;
typedef vector3<ushort>	ushort3;
typedef vector3<int>	int3;
typedef vector3<uint>	uint3;
typedef vector3<long>	long3;
typedef vector3<ulong>	ulong3;
typedef vector3<float>	float3;
typedef vector3<double>	double3;

typedef vector4<char>	char4;
typedef vector4<uchar>	uchar4;
typedef vector4<short>	short4;
typedef vector4<ushort>	ushort4;
typedef vector4<int>	int4;
typedef vector4<uint>	uint4;
typedef vector4<long>	long4;
typedef vector4<ulong>	ulong4;
typedef vector4<float>	float4;
typedef vector4<double>	double4;

template <typename type>
class vector2
{
public:
	typedef type value_type;
	typedef size_t size_type;
	typedef type* pointer;
	typedef const type* const_pointer;
	typedef type& reference;
	typedef const type& const_reference;

public:
	vector2() = default;
	~vector2() = default;

	constexpr vector2(value_type _x, value_type _y)
		: x(_x), y(_y)
	{
	}

	constexpr vector2(const value_type(&_data)[2])
		: x(_data[0]), y(_data[1])
	{
	}

	vector2& absolute()
	{
		x = abs(x);
		y = abs(y);
		return *this;
	}

	vector2 absoluted() const
	{
		return vector2<value_type>(abs(x), abs(y));
	}

	vector2& saturate()
	{
		x = clamp(x, static_cast<value_type>(0.0), static_cast<value_type>(1.0));
		y = clamp(y, static_cast<value_type>(0.0), static_cast<value_type>(1.0));
		return *this;
	}

	vector2 saturated() const
	{
		return vector2<value_type>(clamp(x, static_cast<value_type>(0.0), static_cast<value_type>(1.0)), clamp(y, static_cast<value_type>(0.0), static_cast<value_type>(1.0)));
	}

	value_type squared_length() const
	{
		return x * x + y * y;
	}

	value_type length() const
	{
		return sqrt(squared_length());
	}

	vector2& normalize()
	{
		value_type len = length();
		if (len > static_cast<value_type>(0.0))
		{
			x /= len;
			y /= len;
		}
		else
		{
			*this = zero();
		}
		return *this;
	}

	vector2 normalized() const
	{
		value_type len = length();
		if (len > static_cast<value_type>(0.0))
		{
			return vector2<value_type>(x / len, y / len);
		}
		return zero();
	}

	value_type dot(const vector2<value_type>& _vector) const
	{
		return x * _vector.x + y * _vector.y;
	}

	value_type cross(const vector2<value_type>& _vector) const
	{
		return x * _vector.y - y * _vector.x;
	}

	value_type squared_distance(const vector2<value_type>& _end) const
	{
		auto d = _end - *this;
		return d.squared_length();
	}

	value_type distance(const vector2<value_type>& _end) const
	{
		auto d = _end - *this;
		return d.length();
	}

	bool all() const
	{
		return *this == zero();
	}

	bool any() const
	{
		return *this != zero();
	}

	/*
	vector2& rotate(value_type radian)
	{
		vector2<value_type> vector(x, y);
		value_type sin_angle = sin(radian);
		value_type cos_angle = cos(radian);
		x = vector.x * cos_angle - vector.y * sin_angle;
		y = vector.x * sin_angle + vector.y * cos_angle;
		return *this;
	}
	*/

public:
	vector2& operator=(const vector2& _vector)
	{
		x = _vector.x;
		y = _vector.y;
		return *this;
	}

	vector2 operator+(const vector2& _vector) const
	{
		return vector2<value_type>(x + _vector.x, y + _vector.y);
	}

	vector2& operator+=(const vector2& _vector)
	{
		x += _vector.x;
		y += _vector.y;
		return *this;
	}

	vector2 operator-(const vector2& _vector) const
	{
		return vector2<value_type>(x - _vector.x, y - _vector.y);
	}

	vector2& operator-=(const vector2& _vector)
	{
		x -= _vector.x;
		y -= _vector.y;
		return *this;
	}

	vector2 operator*(const vector2& _vector) const
	{
		return vector2<value_type>(x * _vector.x, y * _vector.y);
	}

	vector2 operator*(value_type _value) const
	{
		return vector2<value_type>(x * _value, y * _value);
	}

	vector2& operator*=(const vector2& _vector)
	{
		x *= _vector.x;
		y *= _vector.y;
		return *this;
	}

	vector2& operator*=(value_type _value)
	{
		x *= _value;
		y *= _value;
		return *this;
	}

	vector2 operator/(const vector2& _vector) const
	{
		return vector2<value_type>(x / vector.x, y / vector.y);
	}

	vector2 operator/(value_type value) const
	{
		return vector2<value_type>(x / value, y / value);
	}

	vector2& operator/=(const vector2& _vector)
	{
		x /= vector.x;
		y /= vector.y;
		return *this;
	}

	vector2& operator/=(value_type _value)
	{
		x /= _value;
		y /= _value;
		return *this;
	}
	
	bool operator==(const vector2& _vector) const
	{
		return (x == _vector.x && y == _vector.y);
	}

	bool operator!=(const vector2& _vector) const
	{
		return (x != _vector.x || y != _vector.y);
	}

	bool operator>(const vector2& _vector) const
	{
		return squared_length() > _vector.squared_length();
	}

	bool operator>=(const vector2& _vector) const
	{
		return squared_length() >= _vector.squared_length();
	}

	bool operator<(const vector2& _vector) const
	{
		return squared_length() < _vector.squared_length();
	}

	bool operator<=(const vector2& _vector) const
	{
		return squared_length() <= _vector.squared_length();
	}

	vector2 operator+() const
	{
		return vector2<value_type>(x, y);
	}

	vector2 operator-() const
	{
		return vector2<value_type>(-x, -y);
	}

	const value_type& operator[](uint index) const
	{
		return data[index];
	}

	value_type& operator[](uint index)
	{
		return data[index];
	}

	operator char2() const
	{
		return char2(static_cast<char>(x), static_cast<char>(y));
	}

	operator uchar2() const
	{
		return uchar2(static_cast<uchar>(x), static_cast<uchar>(y));
	}

	operator short2() const
	{
		return short2(static_cast<short>(x), static_cast<short>(y));
	}

	operator ushort2() const
	{
		return ushort2(static_cast<ushort>(x), static_cast<ushort>(y));
	}

	operator int2() const
	{
		return int2(static_cast<int>(x), static_cast<int>(y));
	}

	operator uint2() const
	{
		return uint2(static_cast<uint>(x), static_cast<uint>(y));
	}

	operator long2() const
	{
		return long2(static_cast<long>(x), static_cast<long>(y));
	}

	operator ulong2() const
	{
		return ulong2(static_cast<ulong>(x), static_cast<ulong>(y));
	}

	operator float2() const
	{
		return float2(static_cast<float>(x), static_cast<float>(y));
	}

	operator double2() const
	{
		return double2(static_cast<double>(x), static_cast<double>(y));
	}
	
public:
	static constexpr vector2 zero()
	{
		return vector2<value_type>(static_cast<value_type>(0.0), static_cast<value_type>(0.0));
	}

	static constexpr vector2 one()
	{
		return vector2<value_type>(static_cast<value_type>(1.0), static_cast<value_type>(1.0));
	}

	static constexpr vector2 unit_x()
	{
		return vector2<value_type>(static_cast<value_type>(1.0), static_cast<value_type>(0.0));
	}

	static constexpr vector2 unit_y()
	{
		return vector2<value_type>(static_cast<value_type>(0.0), static_cast<value_type>(1.0));
	}

	static vector2 random()
	{
		return vector2<value_type>(random<value_type>(), random<value_type>());
	}

	static vector2 random(value_type _minimum, value_type _maximum)
	{
		return vector2<value_type>(random(_minimum, _maximum), random(_minimum, _maximum));
	}

	union
	{
		struct
		{
			value_type x;
			value_type y;
		};
		struct
		{
			value_type r;
			value_type g;
		};
		value_type data[2];
	};
};


template <typename type>
class vector3
{
public:
	typedef type value_type;
	typedef size_t size_type;
	typedef type* pointer;
	typedef const type* const_pointer;
	typedef type& reference;
	typedef const type& const_reference;

public:
	vector3() = default;
	~vector3() = default;

	constexpr vector3(value_type _x, value_type _y, value_type _z)
		: x(_x), y(_y), z(_z)
	{
	}

	constexpr vector3(const vector2<value_type>& _xy, value_type _z)
		: x(_xy.x), y(_xy.y), z(_z)
	{
	}

	constexpr vector3(value_type _x, const vector2<value_type>& _yz)
		: x(_x), y(_yz.x), z(_yz.y)
	{
	}

	constexpr vector3(const value_type(&_data)[3])
		: x(_data[0]), y(_data[1]), z(_data[2])
	{
	}

	vector3& absolute()
	{
		x = abs(x);
		y = abs(y);
		z = abs(z);
		return *this;
	}

	vector3 absoluted() const
	{
		return vector3<value_type>(abs(x), abs(y), abs(z));
	}

	vector3& saturate()
	{
		x = clamp(x, static_cast<value_type>(0.0), static_cast<value_type>(1.0));
		y = clamp(y, static_cast<value_type>(0.0), static_cast<value_type>(1.0));
		z = clamp(z, static_cast<value_type>(0.0), static_cast<value_type>(1.0));
		return *this;
	}

	vector3 saturated() const
	{
		return vector3<value_type>(clamp(x, static_cast<value_type>(0.0), static_cast<value_type>(1.0)), clamp(y, static_cast<value_type>(0.0), static_cast<value_type>(1.0)), clamp(z, static_cast<value_type>(0.0), static_cast<value_type>(1.0)));
	}

	value_type squared_length() const
	{
		return x * x + y * y + z * z;
	}

	value_type length() const
	{
		return sqrt(squared_length());
	}

	vector3& normalize()
	{
		value_type len = length();
		if (len > static_cast<value_type>(0.0))
		{
			x /= len;
			y /= len;
			z /= len;
		}
		else
		{
			*this = zero();
		}
		return *this;
	}

	vector3 normalized() const
	{
		value_type len = length();
		if (len > static_cast<value_type>(0.0))
		{
			return vector3<value_type>(x / len, y / len, z / len);
		}
		return zero();
	}

	value_type dot(const vector3<value_type>& _vector) const
	{
		return x * _vector.x + y * _vector.y + z * _vector.z;
	}

	vector3 cross(const vector3<value_type>& _vector) const
	{
		return vector3<value_type>(y * _vector.z - z * _vector.y, z * _vector.x - x * _vector.z, x * _vector.y - y * _vector.x);
	}

	value_type squared_distance(const vector3<value_type>& _end) const
	{
		auto d = _end - *this;
		return d.squared_length();
	}

	value_type distance(const vector3<value_type>& _end) const
	{
		auto d = _end - *this;
		return d.length();
	}

	bool all() const
	{
		return *this == zero();
	}

	bool any() const
	{
		return *this != zero();
	}

public:
	vector3& operator=(const vector3& _vector)
	{
		x = _vector.x;
		y = _vector.y;
		z = _vector.z;
		return *this;
	}

	vector3 operator+(const vector3& _vector) const
	{
		return vector3<value_type>(x + _vector.x, y + _vector.y, z + _vector.z);
	}

	vector3& operator+=(const vector3& _vector)
	{
		x += _vector.x;
		y += _vector.y;
		z += _vector.z;
		return *this;
	}

	vector3 operator-(const vector3& _vector) const
	{
		return vector3<value_type>(x - _vector.x, y - _vector.y, z - _vector.z);
	}

	vector3& operator-=(const vector3& _vector)
	{
		x -= _vector.x;
		y -= _vector.y;
		z -= _vector.z;
		return *this;
	}

	vector3 operator*(const vector3& _vector) const
	{
		return vector3<value_type>(x * _vector.x, y * _vector.y, z * _vector.z);
	}

	vector3 operator*(value_type _value) const
	{
		return vector3<value_type>(x * _value, y * _value, z * _value);
	}

	vector3& operator*=(const vector3& _vector)
	{
		x *= _vector.x;
		y *= _vector.y;
		z *= _vector.z;
		return *this;
	}

	vector3& operator*=(value_type _value)
	{
		x *= _value;
		y *= _value;
		z *= _value;
		return *this;
	}

	vector3 operator/(const vector3& _vector) const
	{
		return vector3<value_type>(x / _vector.x, y / _vector.y, z / _vector.z);
	}

	vector3 operator/(value_type _value) const
	{
		return vector3<value_type>(x / _value, y / _value, z / _value);
	}

	vector3& operator/=(const vector3& _vector)
	{
		x /= _vector.x;
		y /= _vector.y;
		z /= _vector.z;
		return *this;
	}

	vector3& operator/=(value_type _value)
	{
		x /= _value;
		y /= _value;
		z /= _value;
		return *this;
	}

	bool operator==(const vector3& _vector) const
	{
		return (x == _vector.x && y == _vector.y && z == _vector.z);
	}

	bool operator!=(const vector3& _vector) const
	{
		return (x != _vector.x || y != _vector.y || z != _vector.z);
	}

	bool operator>(const vector3& _vector) const
	{
		return squared_length() > _vector.squared_length();
	}

	bool operator>=(const vector3& _vector) const
	{
		return squared_length() >= _vector.squared_length();
	}

	bool operator<(const vector3& _vector) const
	{
		return squared_length() < _vector.squared_length();
	}

	bool operator<=(const vector3& _vector) const
	{
		return squared_length() <= _vector.squared_length();
	}

	vector3 operator+() const
	{
		return vector3<value_type>(x, y, z);
	}

	vector3 operator-() const
	{
		return vector3<value_type>(-x, -y, -z);
	}

	value_type operator[](uint _index) const
	{
		return data[_index];
	}

	value_type& operator[](uint _index)
	{
		return data[_index];
	}

	operator char3() const
	{
		return char3(static_cast<char>(x), static_cast<char>(y), static_cast<char>(z));
	}

	operator uchar3() const
	{
		return uchar3(static_cast<uchar>(x), static_cast<uchar>(y), static_cast<uchar>(z));
	}

	operator short3() const
	{
		return short3(static_cast<short>(x), static_cast<short>(y), static_cast<short>(z));
	}

	operator ushort3() const
	{
		return ushort3(static_cast<ushort>(x), static_cast<ushort>(y), static_cast<ushort>(z));
	}

	operator int3() const
	{
		return int3(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z));
	}

	operator uint3() const
	{
		return uint3(static_cast<uint>(x), static_cast<uint>(y), static_cast<uint>(z));
	}

	operator long3() const
	{
		return long3(static_cast<long>(x), static_cast<long>(y), static_cast<long>(z));
	}

	operator ulong3() const
	{
		return ulong3(static_cast<ulong>(x), static_cast<ulong>(y), static_cast<ulong>(z));
	}

	operator float3() const
	{
		return float3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
	}

	operator double3() const
	{
		return double3(static_cast<double>(x), static_cast<double>(y), static_cast<double>(z));
	}

public:
	static constexpr vector3 zero()
	{
		return vector3<value_type>(static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0));
	}

	static constexpr vector3 one()
	{
		return vector3<value_type>(static_cast<value_type>(1.0), static_cast<value_type>(1.0), static_cast<value_type>(1.0));
	}

	static constexpr vector3 unit_x()
	{
		return vector3<value_type>(static_cast<value_type>(1.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0));
	}

	static constexpr vector3 unit_y()
	{
		return vector3<value_type>(static_cast<value_type>(0.0), static_cast<value_type>(1.0), static_cast<value_type>(0.0));
	}

	static constexpr vector3 unit_z()
	{
		return vector3<value_type>(static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(1.0));
	}

	static vector3 random()
	{
		return vector3<value_type>(random<value_type>(), random<value_type>(), random<value_type>());
	}

	static vector3 random(value_type _minimum, value_type _maximum)
	{
		return vector3<value_type>(random(_minimum, _maximum), random(_minimum, _maximum), random(_minimum, _maximum));
	}

public:
	union
	{
		struct
		{
			value_type x;
			value_type y;
			value_type z;
		};
		struct
		{
			value_type r;
			value_type g;
			value_type b;
		};
		value_type data[3];
	};
};


template <typename type>
class vector4
{
public:
	typedef type value_type;
	typedef size_t size_type;
	typedef type* pointer;
	typedef const type* const_pointer;
	typedef type& reference;
	typedef const type& const_reference;

public:
	vector4() = default;
	~vector4() = default;

	constexpr vector4(value_type _x, value_type _y, value_type _z, value_type _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	constexpr vector4(const vector2<value_type>& _xy, value_type _z, value_type _w)
		: x(_xy.x), y(_xy.y), z(_z), w(_w)
	{
	}

	constexpr vector4(value_type _x, const vector2<value_type>& _yz, value_type _w)
		: x(_x), y(_yz.x), z(_yz.y), w(_w)
	{
	}

	constexpr vector4(value_type _x, value_type _y, const vector2<value_type>& _zw)
		: x(_x), y(_y), z(_zw.x), w(_zw.y)
	{
	}

	constexpr vector4(const vector2<value_type>& _xy, const vector2<value_type>& _zw)
		: x(_xy.x), y(_xy.y), z(_zw.x), w(_zw.y)
	{
	}

	constexpr vector4(const vector3<value_type>& _xyz, value_type _w)
		: x(_xyz.x), y(_xyz.y), z(_xyz.z), w(_w)
	{
	}

	constexpr vector4(value_type _x, const vector3<value_type>& _yzw)
		: x(_x), y(_yzw.x), z(_yzw.y), w(_yzw.z)
	{
	}

	constexpr vector4(const value_type(&_data)[4])
		: x(_data[0]), y(_data[1]), z(_data[2]), w(_data[3])
	{
	}

	vector4& absolute()
	{
		x = abs(x);
		y = abs(y);
		z = abs(z);
		w = abs(w);
		return *this;
	}

	vector4 absoluted() const
	{
		return vector4<value_type>(abs(x), abs(y), abs(z), abs(w));
	}

	vector4& saturate()
	{
		x = clamp(x, static_cast<value_type>(0.0), static_cast<value_type>(1.0));
		y = clamp(y, static_cast<value_type>(0.0), static_cast<value_type>(1.0));
		z = clamp(z, static_cast<value_type>(0.0), static_cast<value_type>(1.0));
		w = clamp(w, static_cast<value_type>(0.0), static_cast<value_type>(1.0));
		return *this;
	}

	vector4 saturated() const
	{
		return vector4<value_type>(clamp(x, static_cast<value_type>(0.0), static_cast<value_type>(1.0)), clamp(y, static_cast<value_type>(0.0), static_cast<value_type>(1.0)), clamp(z, static_cast<value_type>(0.0), static_cast<value_type>(1.0)), clamp(w, static_cast<value_type>(0.0), static_cast<value_type>(1.0)));
	}

	value_type squared_length() const
	{
		return x * x + y * y + z * z + w * w;
	}

	value_type length() const
	{
		return sqrt(squared_length());
	}

	vector4& normalize()
	{
		value_type len = length();
		if (len > static_cast<value_type>(0.0))
		{
			x /= len;
			y /= len;
			z /= len;
			w /= len;
		}
		else
		{
			*this = zero();
		}
		return *this;
	}

	vector4 normalized() const
	{
		value_type len = length();
		if (len > static_cast<value_type>(0.0))
		{
			return vector4<value_type>(x / len, y / len, z / len, w / len);
		}
		return zero();
	}

	value_type dot(const vector4<value_type>& _vector) const
	{
		return x * _vector.x + y * _vector.y + z * _vector.z + w * _vector.w;
	}

	value_type squared_distance(const vector4<value_type>& _end) const
	{
		auto d = _end - *this;
		return d.squared_length();
	}

	value_type distance(const vector4<value_type>& _end) const
	{
		auto d = _end - *this;
		return d.length();
	}

	bool all() const
	{
		return *this == zero();
	}

	bool any() const
	{
		return *this != zero();
	}

public:
	vector4& operator=(const vector4& vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
		w = vector.w;
		return *this;
	}

	vector4 operator+(const vector4& vector) const
	{
		return vector4<value_type>(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
	}

	vector4& operator+=(const vector4& vector)
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
		w += vector.w;
		return *this;
	}

	vector4 operator-(const vector4& vector) const
	{
		return vector4<value_type>(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
	}

	vector4& operator-=(const vector4& vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		w -= vector.w;
		return *this;
	}

	vector4 operator*(const vector4& vector) const
	{
		return vector4<value_type>(x * vector.x, y * vector.y, z * vector.z, w * vector.w);
	}

	vector4 operator*(value_type value) const
	{
		return vector4<value_type>(x * value, y * value, z * value, w * value);
	}

	vector4& operator*=(const vector4& vector)
	{
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
		w *= vector.w;
		return *this;
	}

	vector4& operator*=(value_type value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}

	vector4 operator/(const vector4& vector) const
	{
		return vector4<value_type>(x / vector.x, y / vector.y, z / vector.z, w / vector.w);
	}

	vector4 operator/(value_type value) const
	{
		return vector4<value_type>(x / value, y / value, z / value, w / value);
	}

	vector4& operator/=(const vector4& vector)
	{
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;
		w /= vector.w;
		return *this;
	}

	vector4& operator/=(value_type value)
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}

	bool operator==(const vector4& vector) const
	{
		return (x == vector.x && y == vector.y && z == vector.z && w == vector.w);
	}

	bool operator!=(const vector4& vector) const
	{
		return (x != vector.x || y != vector.y || z != vector.z || w != vector.w);
	}

	bool operator>(const vector4& _vector) const
	{
		return squared_length() > _vector.squared_length();
	}

	bool operator>=(const vector4& _vector) const
	{
		return squared_length() >= _vector.squared_length();
	}

	bool operator<(const vector4& _vector) const
	{
		return squared_length() < _vector.squared_length();
	}

	bool operator<=(const vector4& _vector) const
	{
		return squared_length() <= _vector.squared_length();
	}

	vector4 operator+() const
	{
		return vector4<value_type>(x, y, z, w);
	}

	vector4 operator-() const
	{
		return vector4<value_type>(-x, -y, -z, -w);
	}

	const value_type& operator[](uint index) const
	{
		return data[index];
	}

	value_type& operator[](uint index)
	{
		return data[index];
	}

	operator char4() const
	{
		return char4(static_cast<char>(x), static_cast<char>(y), static_cast<char>(z), static_cast<char>(w));
	}

	operator uchar4() const
	{
		return uchar4(static_cast<uchar>(x), static_cast<uchar>(y), static_cast<uchar>(z), static_cast<uchar>(w));
	}

	operator short4() const
	{
		return short4(static_cast<short>(x), static_cast<short>(y), static_cast<short>(z), static_cast<short>(w));
	}

	operator ushort4() const
	{
		return ushort4(static_cast<ushort>(x), static_cast<ushort>(y), static_cast<ushort>(z), static_cast<ushort>(w));
	}

	operator int4() const
	{
		return int4(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z), static_cast<int>(w));
	}

	operator uint4() const
	{
		return uint4(static_cast<uint>(x), static_cast<uint>(y), static_cast<uint>(z), static_cast<uint>(w));
	}

	operator long4() const
	{
		return long4(static_cast<long>(x), static_cast<long>(y), static_cast<long>(z), static_cast<long>(w));
	}

	operator ulong4() const
	{
		return ulong4(static_cast<ulong>(x), static_cast<ulong>(y), static_cast<ulong>(z), static_cast<ulong>(w));
	}

	operator float4() const
	{
		return float4(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w));
	}

	operator double4() const
	{
		return double4(static_cast<double>(x), static_cast<double>(y), static_cast<double>(z), static_cast<double>(w));
	}

public:
	static constexpr vector4 zero()
	{
		return vector4<value_type>(static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0));
	}

	static constexpr vector4 one()
	{
		return vector4<value_type>(static_cast<value_type>(1.0), static_cast<value_type>(1.0), static_cast<value_type>(1.0), static_cast<value_type>(1.0));
	}

	static constexpr vector4 unit_x()
	{
		return vector4<value_type>(static_cast<value_type>(1.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0));
	}

	static constexpr vector4 unit_y()
	{
		return vector4<value_type>(static_cast<value_type>(0.0), static_cast<value_type>(1.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0));
	}

	static constexpr vector4 unit_z()
	{
		return vector4<value_type>(static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(1.0), static_cast<value_type>(0.0));
	}

	static constexpr vector4 unit_w()
	{
		return vector4<value_type>(static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(1.0));
	}

	static vector4 random()
	{
		return vector4<value_type>(random<value_type>(), random<value_type>(), random<value_type>(), random<value_type>());
	}

	static vector4 random(value_type _minimum, value_type _maximum)
	{
		return vector4<value_type>(random(_minimum, _maximum), random(_minimum, _maximum), random(_minimum, _maximum), random(_minimum, _maximum));
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
			value_type r;
			value_type g;
			value_type b;
			value_type a;
		};
		value_type data[4];
	};
};

template<typename value_type, typename CharT> inline std::basic_ostream<CharT>& operator <<(std::basic_ostream<CharT>& os, const vector2<value_type>& vector)
{
	return os << '(' << vector.x << ',' << vector.y << ')';
}

template<typename value_type, typename CharT> inline std::basic_istream<CharT>& operator >>(std::basic_istream<CharT>& is, vector2<value_type>& vector)
{
	CharT dummy;
	return is >> dummy >> vector.x >> dummy >> vector.y >> dummy;
}

template<typename value_type, typename CharT> inline std::basic_ostream<CharT>& operator <<(std::basic_ostream<CharT>& os, const vector3<value_type>& vector)
{
	return os << '(' << vector.x << ',' << vector.y << ',' << vector.z << ')';
}

template<typename value_type, typename CharT> inline std::basic_istream<CharT>& operator >> (std::basic_istream<CharT>& is, vector3<value_type>& vector)
{
	CharT dummy;
	return is >> dummy >> vector.x >> dummy >> vector.y >> dummy >> vector.z >> dummy;
}

template<typename value_type, typename CharT> inline std::basic_ostream<CharT>& operator <<(std::basic_ostream<CharT>& os, const vector4<value_type>& vector)
{
	return os << '(' << vector.x << ',' << vector.y << ',' << vector.z << ',' << vector.w << ')';
}

template<typename value_type, typename CharT> inline std::basic_istream<CharT>& operator >> (std::basic_istream<CharT>& is, vector4<value_type>& vector)
{
	CharT dummy;
	return is >> dummy >> vector.x >> dummy >> vector.y >> dummy >> vector.z >> dummy >> vector.w >> dummy;
}

template <typename value_type> inline vector2<value_type> swizzle(const vector2<value_type>& vector, unsigned int x, unsigned int y)
{
	return vector2<value_type>(vector[x], vector[y]);
}

template <typename value_type> inline vector2<value_type> swizzle(const vector3<value_type>& vector, unsigned int x, unsigned int y)
{
	return vector2<value_type>(vector[x], vector[y]);
}

template <typename value_type> inline vector2<value_type> swizzle(const vector4<value_type>& vector, unsigned int x, unsigned int y)
{
	return vector2<value_type>(vector[x], vector[y]);
}

template <typename value_type> inline vector3<value_type> swizzle(const vector2<value_type>& vector, unsigned int x, unsigned int y, unsigned int z)
{
	return vector3<value_type>(vector[x], vector[y], vector[z]);
}

template <typename value_type> inline vector3<value_type> swizzle(const vector3<value_type>& vector, unsigned int x, unsigned int y, unsigned int z)
{
	return vector3<value_type>(vector[x], vector[y], vector[z]);
}

template <typename value_type> inline vector3<value_type> swizzle(const vector4<value_type>& vector, unsigned int x, unsigned int y, unsigned int z)
{
	return vector3<value_type>(vector[x], vector[y], vector[z]);
}

template <typename value_type> inline vector4<value_type> swizzle(const vector2<value_type>& vector, unsigned int x, unsigned int y, unsigned int z, unsigned int w)
{
	return vector4<value_type>(vector[x], vector[y], vector[z], vector[w]);
}

template <typename value_type> inline vector4<value_type> swizzle(const vector3<value_type>& vector, unsigned int x, unsigned int y, unsigned int z, unsigned int w)
{
	return vector4<value_type>(vector[x], vector[y], vector[z], vector[w]);
}

template <typename value_type> inline vector4<value_type> swizzle(const vector4<value_type>& vector, unsigned int x, unsigned int y, unsigned int z, unsigned int w)
{
	return vector4<value_type>(vector[x], vector[y], vector[z], vector[w]);
}

}