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

template<class error_type, class value_type>
class unexpected final
{
public:
	constexpr unexpected()
		: m_error(true)
	{
	}

	constexpr unexpected(error_type _error)
		: m_error(true), m_error(_error)
	{
	}

	constexpr unexpected(value_type _value)
		: m_error(false), m_value(_value)
	{
	}

	~unexpected() = default;

	error_type& error()
	{
		return m_value;
	}

	const error_type& error() const
	{
		return m_value;
	}

	value_type& value()
	{
		return m_value;
	}

	const value_type& value() const
	{
		return m_value;
	}

	operator bool() const
	{
		return !m_has_error;
	}

private:
	bool m_has_error;
	error_type m_error;
	value_type m_value;
};

template<class error_type, class value_type> inline unexpected<error_type, value_type> make_unexpected(error_type _error)
{
	return std::move(unexpected<error_type, value_type>(_error));
}

}