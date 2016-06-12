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

template <typename type> class matrix3x3;

typedef matrix3x3<char> char3x3;
typedef matrix3x3<uchar> uchar3x3;
typedef matrix3x3<short> short3x3;
typedef matrix3x3<ushort> ushort3x3;
typedef matrix3x3<int> int3x3;
typedef matrix3x3<uint> uint3x3;
typedef matrix3x3<long> long3x3;
typedef matrix3x3<ulong> ulong3x3;
typedef matrix3x3<float> float3x3;
typedef matrix3x3<double> double3x3;
	
template <typename type>
class matrix3x3
{
public:
	typedef type value_type;
	typedef size_t size_type;
	typedef type* pointer;
	typedef const type* const_pointer;
	typedef type& reference;
	typedef const type& const_reference;

public:
	matrix3x3() = default;

	constexpr matrix3x3(
		value_type _11, value_type _12, value_type _13,
		value_type _21, value_type _22, value_type _23,
		value_type _31, value_type _32, value_type _33)
		:_11(_11), _12(_12), _13(_13),
		_21(_21), _22(_22), _23(_23),
		_31(_31), _32(_32), _33(_33)
	{
	}

	constexpr matrix3x3(value_type _11, value_type _22, value_type _33)
		:_11(_11), _12(static_cast<value_type>(0.0)), _13(static_cast<value_type>(0.0)),
		_21(static_cast<value_type>(0.0)), _22(_22), _23(static_cast<value_type>(0.0)),
		_31(static_cast<value_type>(0.0)), _32(static_cast<value_type>(0.0)), _33(_33)
	{
	}

	constexpr matrix3x3(const value_type(&data)[9])
		:_11(data[0]), _12(data[1]), _13(data[2]),
		_21(data[3]), _22(data[4]), _23(data[5]),
		_31(data[6]), _32(data[7]), _33(data[8])
	{
	}

	///	<summary>行数を取得します。</summary>
	constexpr size_type rows() const
	{
		return 3;
	}

	///	<summary>列数を取得します。</summary>
	constexpr size_type columns() const
	{
		return 3;
	}

	constexpr size_type size() const
	{
		return 9;
	}

	constexpr value_type determinant() const
	{
		return
			_11 * _22 * _33 + _21 * _32 * _13 + _31 * _12 * _23 -
			_31 * _22 * _13 - _21 * _12 * _33 - _11 * _32 * _23;
	}

	constexpr matrix3x3 cofactor() const
	{
		return matrix3x3<value_type>
			(
				_22 * _33 - _23 * _32,
				_13 * _32 - _12 * _33,
				_12 * _23 - _13 * _22,
				_23 * _31 - _21 * _33,
				_11 * _33 - _13 * _31,
				_13 * _21 - _11 * _23,
				_21 * _32 - _22 * _31,
				_12 * _31 - _11 * _32,
				_11 * _22 - _12 * _21
				);
	}

	matrix3x3 inverse() const
	{
		value_type det = determinant();
		return (det != 0) ? cofactor() / det : identity();
	}

	constexpr matrix3x3 inverse(value_type& _determinant) const
	{
		_determinant = determinant();
		return (_determinant != 0) ? cofactor() / _determinant : identity();
	}

	matrix3x3 transpose() const
	{
		return matrix3x3<value_type>
			(
				_11, _21, _31,
				_12, _22, _32,
				_13, _23, _33
				);
	}

	constexpr matrix3x3 rotated(value_type roll, value_type pitch, value_type yaw) const
	{
		return *this * rotation(roll, pitch, yaw);
	}

	constexpr matrix3x3 translated(value_type _x, value_type _y, value_type _z) const
	{
		return *this * translation(_x, _y, _z);
	}

	constexpr matrix3x3 translated(const vector3<value_type>& _offset) const
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

public:
	matrix3x3& operator=(const matrix3x3& _matrix)
	{
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				data[y][x] = _matrix.data[y][x];
			}
		}
		return *this;
	}

	matrix3x3 operator+(const matrix3x3& _matrix) const
	{
		matrix3x3<value_type> mat;
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				mat.data[y][x] = data[y][x] + _matrix.data[y][x];
			}
		}
		return std::move(mat);
	}

	matrix3x3& operator+=(const matrix3x3& _matrix)
	{
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				data[y][x] += _matrix.data[y][x];
			}
		}
		return *this;
	}

	matrix3x3 operator-(const matrix3x3& _matrix) const
	{
		matrix3x3<value_type> mat;
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				mat.data[y][x] = data[y][x] - _matrix.data[y][x];
			}
		}
		return std::move(mat);
	}

	matrix3x3& operator-=(const matrix3x3& _matrix)
	{
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				data[y][x] -= _matrix.data[y][x];
			}
		}
		return *this;
	}

	matrix3x3 operator*(const matrix3x3& _matrix) const
	{
		matrix3x3<value_type> mat = zero();
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				for (size_t i = 0; i < 3; i++)
				{
					mat.data[y][x] += data[y][i] * _matrix.data[i][x];
				}
			}
		}
		return std::move(mat);
	}

	matrix3x3 operator*(value_type value) const
	{
		matrix3x3<value_type> mat;
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				mat.data[y][x] = data[y][x] * value;
			}
		}
		return std::move(mat);
	}

	matrix3x3& operator*=(const matrix3x3& _matrix)
	{
		*this = std::move(*this * _matrix);
		return *this;
	}

	matrix3x3& operator*=(value_type value)
	{
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				data[y][x] *= value;
			}
		}
		return *this;
	}

	matrix3x3 operator/(value_type value) const
	{
		matrix3x3<value_type> mat;
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				mat.data[y][x] = data[y][x] / value;
			}
		}
		return std::move(mat);
	}

	matrix3x3& operator/=(value_type value)
	{
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				data[y][x] /= value;
			}
		}
		return *this;
	}

	bool operator==(const matrix3x3& vector) const
	{
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				if (data[y][x] != value)
				{
					return false;
				}
			}
		}
		return true;
	}

	bool operator!=(const matrix3x3& vector) const
	{
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				if (data[y][x] != value)
				{
					return true;
				}
			}
		}
		return false;
	}

	matrix3x3 operator+() const
	{
		matrix3x3<value_type> mat;
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				mat.data[y][x] = data[y][x];
			}
		}
		return std::move(mat);
	}

	matrix3x3 operator-() const
	{
		matrix3x3<value_type> mat;
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 3; x++)
			{
				mat.data[y][x] = -data[y][x];
			}
		}
		return std::move(mat);
	}

	value_type operator()(size_type _row, size_type _column) const
	{
		return data[_row][_column];
	}

	value_type& operator()(size_type _row, size_type _column)
	{
		return data[_row][_column];
	}

	const value_type* operator[](size_type _row) const
	{
		return data[_row];
	}

	value_type* operator[](size_type _row)
	{
		return data[_row];
	}

public:
	static constexpr matrix3x3 zero()
	{
		return matrix3x3<value_type>
			(
				static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0),
				static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0),
				static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0)
				);
	}

	static constexpr matrix3x3 identity()
	{
		return matrix3x3<value_type>
			(
				static_cast<value_type>(1.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0),
				static_cast<value_type>(0.0), static_cast<value_type>(1.0), static_cast<value_type>(0.0),
				static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(1.0)
				);
	}

	static constexpr matrix3x3 translation(value_type x, value_type y, value_type z)
	{
		return matrix3x3<value_type>
			(
				static_cast<value_type>(1.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0),
				static_cast<value_type>(0.0), static_cast<value_type>(1.0), static_cast<value_type>(0.0),
				x, y, z
				);
	}

	static constexpr matrix3x3 translation(const vector3<value_type>& offset)
	{
		return matrix3x3<value_type>
			(
				static_cast<value_type>(1.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0),
				static_cast<value_type>(0.0), static_cast<value_type>(1.0), static_cast<value_type>(0.0),
				offset.x, offset.y, offset.z
				);
	}

	static matrix3x3 roll(value_type roll)
	{
		const value_type roll_sin = sin(roll);
		const value_type roll_cos = cos(roll);

		return matrix3x3<value_type>
			(
				roll_cos, -roll_sin, static_cast<value_type>(0.0),
				roll_sin, roll_cos, static_cast<value_type>(0.0),
				static_cast<value_type>(0.0), static_cast<value_type>(0.0), static_cast<value_type>(1.0)
				);
	}

	static matrix3x3 pitch(value_type pitch)
	{
		const value_type pitch_sin = sin(pitch);
		const value_type pitch_cos = cos(pitch);

		return matrix3x3<value_type>
			(
				static_cast<value_type>(1.0), static_cast<value_type>(0.0), static_cast<value_type>(0.0),
				static_cast<value_type>(0.0), pitch_cos, -pitch_sin,
				static_cast<value_type>(0.0), pitch_sin, pitch_cos
				);
	}

	static matrix3x3 yaw(value_type yaw)
	{
		const value_type yaw_sin = sin(yaw);
		const value_type yaw_cos = cos(yaw);

		return matrix3x3<value_type>
			(
				yaw_cos, static_cast<value_type>(0.0), yaw_sin,
				static_cast<value_type>(0.0), static_cast<value_type>(1.0), static_cast<value_type>(0.0),
				-yaw_sin, static_cast<value_type>(0.0), yaw_cos
				);
	}

	static matrix3x3 rotation(value_type roll, value_type pitch, value_type yaw)
	{
		const value_type roll_sin = sin(roll);
		const value_type roll_cos = cos(roll);
		const value_type pitch_sin = sin(pitch);
		const value_type pitch_cos = cos(pitch);
		const value_type yaw_sin = sin(yaw);
		const value_type yaw_cos = cos(yaw);

		return matrix3x3<value_type>
			(
				yaw_sin * pitch_sin * roll_sin + yaw_cos * roll_cos, yaw_sin * pitch_sin * roll_cos - yaw_cos * roll_sin, yaw_sin * pitch_cos,
				pitch_cos * roll_sin, pitch_cos * roll_cos, -pitch_sin,
				yaw_cos * pitch_sin * roll_sin - yaw_sin * roll_cos, yaw_cos * pitch_sin * roll_cos + yaw_sin * roll_sin, yaw_cos * pitch_cos
				);
	}

	//conjugate();
public:
	union
	{
		struct
		{
			value_type _11; value_type _12; value_type _13;
			value_type _21; value_type _22; value_type _23;
			value_type _31; value_type _32; value_type _33;
		};
		value_type data[3][3];
	};
};

template<typename T, typename CharT> inline std::basic_ostream<CharT>& operator <<(std::basic_ostream<CharT>& os, const matrix3x3<T>& matrix)
{
	os << '(';
	os << '(' << matrix._11 << ',' << matrix._12 << ',' << matrix._13 << ')' << ',';
	os << '(' << matrix._21 << ',' << matrix._22 << ',' << matrix._23 << ')' << ',';
	os << '(' << matrix._31 << ',' << matrix._32 << ',' << matrix._33 << ')' << ')';
	return os;
}

template<typename T, typename CharT> inline std::basic_istream<CharT>& operator >>(std::basic_istream<CharT>& is, matrix3x3<T>& matrix)
{
	CharT dummy;
	is >> dummy;
	is >> dummy >> matrix._11 >> dummy >> matrix._12 >> dummy >> matrix._13 >> dummy >> dummy;
	is >> dummy >> matrix._21 >> dummy >> matrix._22 >> dummy >> matrix._23 >> dummy >> dummy;
	is >> dummy >> matrix._31 >> dummy >> matrix._32 >> dummy >> matrix._33 >> dummy >> dummy;
	return is;
}

}