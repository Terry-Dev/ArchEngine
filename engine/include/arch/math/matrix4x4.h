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
	
template <typename type> class matrix4x4;

typedef matrix4x4<char>		char4x4;
typedef matrix4x4<uchar>	uchar4x4;
typedef matrix4x4<short>	short4x4;
typedef matrix4x4<ushort>	ushort4x4;
typedef matrix4x4<int>		int4x4;
typedef matrix4x4<uint>		uint4x4;
typedef matrix4x4<long>		long4x4;
typedef matrix4x4<ulong>	ulong4x4;
typedef matrix4x4<float>	float4x4;
typedef matrix4x4<double>	double4x4;
	
template <typename type>
class matrix4x4
{
public:
	typedef type value_type;
	typedef size_t size_type;
	typedef type* pointer;
	typedef const type* const_pointer;
	typedef type& reference;
	typedef const type& const_reference;

public:
	matrix4x4() = default;

	constexpr matrix4x4(
		value_type _11, value_type _12, value_type _13, value_type _14,
		value_type _21, value_type _22, value_type _23, value_type _24,
		value_type _31, value_type _32, value_type _33, value_type _34,
		value_type _41, value_type _42, value_type _43, value_type _44)
		:_11(_11), _12(_12), _13(_13), _14(_14),
		_21(_21), _22(_22), _23(_23), _24(_24),
		_31(_31), _32(_32), _33(_33), _34(_34),
		_41(_41), _42(_42), _43(_43), _44(_44)
	{
	}

	constexpr matrix4x4(value_type _11, value_type _22, value_type _33, value_type _44)
		:_11(_11), _12(static_cast<value_type>(0.0)), _13(static_cast<value_type>(0.0)), _14(static_cast<value_type>(0.0)),
		_21(static_cast<value_type>(0.0)), _22(_22), _23(static_cast<value_type>(0.0)), _24(static_cast<value_type>(0.0)),
		_31(static_cast<value_type>(0.0)), _32(static_cast<value_type>(0.0)), _33(_33), _34(static_cast<value_type>(0.0)),
		_41(static_cast<value_type>(0.0)), _42(static_cast<value_type>(0.0)), _43(static_cast<value_type>(0.0)), _44(_44)
	{
	}

	constexpr matrix4x4(const value_type(&data)[16])
		:_11(data[0]), _12(data[1]), _13(data[2]), _14(data[3]),
		_21(data[4]), _22(data[5]), _23(data[6]), _24(data[7]),
		_31(data[8]), _32(data[9]), _33(data[10]), _34(data[11]),
		_41(data[12]), _42(data[13]), _43(data[14]), _44(data[15])
	{
	}

	constexpr matrix4x4(const vector4<value_type>(&row)[4])
		:_11(row[0].x), _12(row[0].y), _13(row[0].z), _14(row[0].w),
		_21(row[1].x), _22(row[1].y), _23(row[1].z), _24(row[1].w),
		_31(row[2].x), _32(row[2].y), _33(row[2].z), _34(row[2].w),
		_41(row[3].x), _42(row[3].y), _43(row[3].z), _44(row[3].w)
	{
	}

	///	<summary>çsêîÇéÊìæÇµÇ‹Ç∑ÅB</summary>
	constexpr size_type rows() const
	{
		return 4;
	}

	///	<summary>óÒêîÇéÊìæÇµÇ‹Ç∑ÅB</summary>
	constexpr size_type columns() const
	{
		return 4;
	}

	constexpr size_type size() const
	{
		return 16;
	}

	constexpr value_type determinant() const
	{
		return
			_11 * (_22 * (_33 * _44 - _34 * _43) + _23 * (_34 * _42 - _32 * _44) + _24 * (_32 * _43 - _33 * _42)) +
			_21 * (_32 * (_14 * _43 - _13 * _44) + _33 * (_12 * _44 - _14 * _42) + _34 * (_13 * _42 - _12 * _43)) +
			_31 * (_42 * (_13 * _24 - _14 * _23) + _43 * (_14 * _22 - _12 * _24) + _44 * (_12 * _23 - _13 * _22)) +
			_41 * (_12 * (_23 * _34 - _24 * _33) + _13 * (_24 * _32 - _22 * _34) + _14 * (_22 * _33 - _23 * _32));
	}

	constexpr matrix4x4 cofactor() const
	{
		return matrix4x4<value_type>
			(
				_22 * (_33 * _44 - _34 * _43) + _23 * (_34 * _42 - _32 * _44) + _24 * (_32 * _43 - _33 * _42),
				_32 * (_14 * _43 - _13 * _44) + _33 * (_12 * _44 - _14 * _42) + _34 * (_13 * _42 - _12 * _43),
				_42 * (_13 * _24 - _14 * _23) + _43 * (_14 * _22 - _12 * _24) + _44 * (_12 * _23 - _13 * _22),
				_12 * (_23 * _34 - _24 * _33) + _13 * (_24 * _32 - _22 * _34) + _14 * (_22 * _33 - _23 * _32),

				_21 * (_33 * _44 - _34 * _43) + _23 * (_34 * _41 - _31 * _44) + _24 * (_31 * _43 - _33 * _41),
				_31 * (_14 * _43 - _13 * _44) + _33 * (_11 * _44 - _14 * _41) + _34 * (_13 * _41 - _11 * _43),
				_41 * (_13 * _24 - _14 * _23) + _43 * (_14 * _21 - _11 * _24) + _44 * (_11 * _23 - _13 * _21),
				_11 * (_23 * _34 - _24 * _33) + _13 * (_24 * _31 - _21 * _34) + _14 * (_21 * _33 - _23 * _31),

				_21 * (_32 * _44 - _34 * _42) + _22 * (_34 * _41 - _31 * _44) + _24 * (_31 * _42 - _32 * _41),
				_31 * (_14 * _42 - _44 * _12) + _32 * (_11 * _44 - _41 * _14) + _34 * (_12 * _41 - _11 * _42),
				_41 * (_12 * _24 - _14 * _22) + _42 * (_14 * _21 - _11 * _24) + _44 * (_11 * _22 - _12 * _21),
				_11 * (_22 * _34 - _24 * _32) + _12 * (_24 * _31 - _21 * _34) + _14 * (_21 * _32 - _22 * _31),

				_21 * (_32 * _43 - _33 * _42) + _22 * (_33 * _41 - _31 * _43) + _23 * (_31 * _42 - _32 * _41),
				_31 * (_13 * _42 - _12 * _43) + _32 * (_11 * _43 - _13 * _41) + _33 * (_12 * _41 - _11 * _42),
				_41 * (_12 * _23 - _13 * _22) + _42 * (_13 * _21 - _11 * _23) + _43 * (_11 * _22 - _12 * _21),
				_11 * (_22 * _33 - _23 * _32) + _12 * (_23 * _31 - _21 * _33) + _13 * (_21 * _32 - _22 * _31)
				);
	}

	matrix4x4 inverse() const
	{
		auto det = determinant();
		return (det != static_cast<value_type>(0)) ? cofactor() / det : identity();
	}

	constexpr matrix4x4 inverse(value_type& _determinant) const
	{
		_determinant = determinant();
		return (_determinant != 0) ? cofactor() / _determinant : identity();
	}

	matrix4x4 transpose() const
	{
		matrix4x4<value_type> mat;
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				mat.data[x][y] = data[y][x];
			}
		}
		return std::move(mat);
	}

	constexpr matrix4x4 rotated(value_type roll, value_type pitch, value_type yaw) const
	{
		return *this * rotation(roll, picth, yaw);
	}

	constexpr matrix4x4 translated(value_type _x, value_type _y, value_type _z) const
	{
		return *this * translation(_x, _y, _z);
	}

	constexpr matrix4x4 translated(const vector3<value_type>& _offset) const
	{
		return *this * translation(_offset);
	}

	constexpr vector3<value_type> transform(const vector3<value_type>& _vector) const
	{
		return vector3<value_type>
			(
				_11 * _vector.x + _12 * _vector.y + _13 * _vector.z,
				_21 * _vector.x + _22 * _vector.y + _23 * _vector.z,
				_31 * _vector.x + _32 * _vector.y + _33 * _vector.z
				);
	}

	constexpr vector4<value_type> transform(const vector4<value_type>& _vector) const
	{
		return vector3<value_type>
			(
				_11 * _vector.x + _12 * _vector.y + _13 * _vector.z + _14 * _vector.w,
				_21 * _vector.x + _22 * _vector.y + _23 * _vector.z + _24 * _vector.w,
				_31 * _vector.x + _32 * _vector.y + _33 * _vector.z + _24 * _vector.w
				);
	}

public:
	matrix4x4& operator=(const matrix4x4& _matrix)
	{
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				data[y][x] = _matrix.data[y][x];
			}
		}
		return *this;
	}

	matrix4x4 operator+(const matrix4x4& _matrix) const
	{
		matrix4x4<value_type> mat;
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				mat.data[y][x] = data[y][x] + _matrix.data[y][x];
			}
		}
		return std::move(mat);
	}

	matrix4x4& operator+=(const matrix4x4& _matrix)
	{
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				data[y][x] += _matrix.data[y][x];
			}
		}
		return *this;
	}

	matrix4x4 operator-(const matrix4x4& _matrix) const
	{
		matrix4x4<value_type> mat;
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				mat.data[y][x] = data[y][x] - _matrix.data[y][x];
			}
		}
		return std::move(mat);
	}

	matrix4x4& operator-=(const matrix4x4& _matrix)
	{
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				data[y][x] -= _matrix.data[y][x];
			}
		}
		return *this;
	}

	matrix4x4 operator*(const matrix4x4& _matrix) const
	{
		matrix4x4<value_type> mat = zero();
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				for (size_t i = 0; i < 4; i++)
				{
					mat.data[y][x] += data[y][i] * _matrix.data[i][x];
				}
			}
		}
		return std::move(mat);
	}

	matrix4x4 operator*(value_type value) const
	{
		matrix4x4<value_type> mat;
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				mat.data[y][x] = data[y][x] * value;
			}
		}
		return std::move(mat);
	}

	matrix4x4& operator*=(const matrix4x4& _matrix)
	{
		*this = std::move(*this * _matrix);
		return *this;
	}

	matrix4x4& operator*=(value_type value)
	{
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				data[y][x] *= value;
			}
		}
		return *this;
	}

	matrix4x4 operator/(value_type value) const
	{
		matrix4x4<value_type> mat;
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				mat.data[y][x] = data[y][x] / value;
			}
		}
		return std::move(mat);
	}

	matrix4x4& operator/=(value_type value)
	{
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				data[y][x] /= value;
			}
		}
		return *this;
	}

	bool operator==(const matrix4x4& vector) const
	{
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				if (data[y][x] != value)
				{
					return false;
				}
			}
		}
		return true;
	}

	bool operator!=(const matrix4x4& vector) const
	{
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				if (data[y][x] != value)
				{
					return true;
				}
			}
		}
		return false;
	}

	matrix4x4 operator+() const
	{
		matrix4x4<value_type> mat;
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				mat.data[y][x] = data[y][x];
			}
		}
		return std::move(mat);
	}

	matrix4x4 operator-() const
	{
		matrix4x4<value_type> mat;
		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				mat.data[y][x] = -data[y][x];
			}
		}
		return std::move(mat);
	}

	value_type operator()(uint rowIndex, uint columnIndex) const
	{
		return data[rowIndex][columnIndex];
	}

	value_type& operator()(uint rowIndex, uint columnIndex)
	{
		return data[rowIndex][columnIndex];
	}

	const value_type* operator[](uint index) const
	{
		return data[index];
	}

	value_type* operator[](uint index)
	{
		return data[index];
	}

public:
	static constexpr matrix4x4 zero()
	{
		return matrix4x4<value_type>
			(
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0)
				);
	}

	static constexpr matrix4x4 identity()
	{
		return matrix4x4<value_type>
			(
				static_cast<value_type>(1.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0)
				);
	}

	static matrix4x4 roll(value_type roll)
	{
		const value_type roll_sin = sin(roll);
		const value_type roll_cos = cos(roll);

		return matrix4x4<value_type>
			(
				roll_cos,
				-roll_sin,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				roll_sin,
				roll_cos,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0)
				);
	}

	static matrix4x4 pitch(value_type pitch)
	{
		const value_type pitch_sin = sin(pitch);
		const value_type pitch_cos = cos(pitch);

		return matrix4x4<value_type>
			(
				static_cast<value_type>(1.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				pitch_cos,
				-pitch_sin,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				pitch_sin,
				pitch_cos,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0)
				);
	}

	static matrix4x4 yaw(value_type yaw)
	{
		const value_type yaw_sin = sin(yaw);
		const value_type yaw_cos = cos(yaw);

		return matrix4x4<value_type>
			(
				yaw_cos,
				static_cast<value_type>(0.0),
				yaw_sin,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				-yaw_sin,
				static_cast<value_type>(0.0),
				yaw_cos,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0)
				);
	}

	static matrix4x4 rotation(value_type roll, value_type pitch, value_type yaw)
	{
		const value_type roll_sin = sin(roll);
		const value_type roll_cos = cos(roll);
		const value_type pitch_sin = sin(pitch);
		const value_type pitch_cos = cos(pitch);
		const value_type yaw_sin = sin(yaw);
		const value_type yaw_cos = cos(yaw);

		return matrix4x4<value_type>
			(
				yaw_sin * pitch_sin * roll_sin + yaw_cos * roll_cos,
				yaw_sin * pitch_sin * roll_cos - yaw_cos * roll_sin,
				yaw_sin * pitch_cos,
				static_cast<value_type>(0.0),
				pitch_cos * roll_sin,
				pitch_cos * roll_cos,
				-pitch_sin,
				static_cast<value_type>(0.0),
				yaw_cos * pitch_sin * roll_sin - yaw_sin * roll_cos,
				yaw_cos * pitch_sin * roll_cos + yaw_sin * roll_sin,
				yaw_cos * pitch_cos,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0)
				);
	}

	static constexpr matrix4x4 scaling(value_type _scale_x, value_type _scale_y, value_type _scale_z)
	{
		return matrix4x4<value_type>
			(
				_scale_x,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				_scale_y,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				_scale_z,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0)
				);
	}

	static constexpr matrix4x4 scaling(const vector3<value_type>& _scale)
	{
		return matrix4x4<value_type>
			(
				_scale.x,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				_scale.y,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				_scale.z,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0)
				);
	}

	static constexpr matrix4x4 translation(value_type _x, value_type _y, value_type _z)
	{
		return matrix4x4<value_type>
			(
				static_cast<value_type>(1.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0),
				static_cast<value_type>(0.0),
				_x,
				_y,
				_z,
				static_cast<value_type>(1.0)
				);
	}

	static constexpr matrix4x4 translation(const vector3<value_type>& _offset)
	{
		return matrix4x4<value_type>
			(
				static_cast<value_type>(1.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0),
				static_cast<value_type>(0.0),
				_offset.x,
				_offset.y,
				_offset.z,
				static_cast<value_type>(1.0)
				);
	}

	static constexpr matrix4x4 ortho(value_type width, value_type height, value_type near_z, value_type far_z)
	{
		return matrix4x4<value_type>
			(
				static_cast<value_type>(2.0) / width,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(2.0) / height,
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(1.0) / (far_z - near_z),
				static_cast<value_type>(1.0),
				static_cast<value_type>(0.0),
				static_cast<value_type>(0.0),
				near_z / (near_z - far_z),
				static_cast<value_type>(1.0)
				);
	}

public:
	union
	{
		struct
		{
			value_type _11; value_type _12; value_type _13; value_type _14;
			value_type _21; value_type _22; value_type _23; value_type _24;
			value_type _31; value_type _32; value_type _33; value_type _34;
			value_type _41; value_type _42; value_type _43; value_type _44;
		};
		value_type data[4][4];
		value_type m[16];
	};
};

template<typename T, typename CharT> inline std::basic_ostream<CharT>& operator <<(std::basic_ostream<CharT>& os, const matrix4x4<T>& matrix)
{
	os << '(';
	os << '(' << matrix._11 << ',' << matrix._12 << ',' << matrix._13 << ',' << matrix._14 << ')' << ',';
	os << '(' << matrix._21 << ',' << matrix._22 << ',' << matrix._23 << ',' << matrix._24 << ')' << ',';
	os << '(' << matrix._31 << ',' << matrix._32 << ',' << matrix._33 << ',' << matrix._34 << ')' << ',';
	os << '(' << matrix._41 << ',' << matrix._42 << ',' << matrix._43 << ',' << matrix._44 << ')' << ')';
	return os;
}

template<typename T, typename CharT> inline std::basic_istream<CharT>& operator >>(std::basic_istream<CharT>& is, matrix4x4<T>& matrix)
{
	CharT dummy;
	is >> dummy;
	is >> dummy >> matrix._11 >> dummy >> matrix._12 >> dummy >> matrix._13 >> dummy >> matrix._14 >> dummy >> dummy;
	is >> dummy >> matrix._21 >> dummy >> matrix._22 >> dummy >> matrix._23 >> dummy >> matrix._24 >> dummy >> dummy;
	is >> dummy >> matrix._31 >> dummy >> matrix._32 >> dummy >> matrix._33 >> dummy >> matrix._34 >> dummy >> dummy;
	is >> dummy >> matrix._41 >> dummy >> matrix._42 >> dummy >> matrix._43 >> dummy >> matrix._44 >> dummy >> dummy;
	return is;
}

}