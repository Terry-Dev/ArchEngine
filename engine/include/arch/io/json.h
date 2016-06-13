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

#include <map>
#include <memory>
#include <vector>
#include "types.h"

namespace arch
{

namespace json
{

class value;
typedef std::vector<value> array;

class value
{
public:
	value();
	value(const value& _value);
	~value();

	bool read(const std::string& _filepath);
	bool write(const std::string& _filepath) const;

	void set(const std::string& _value);
	template<typename T> void set(const T& _value)
	{
		set<std::string>(to_string(_value));
	}
	template<> void set<array>(const array& _value);
	template<> void set<bool>(const bool& _value);

	std::string get() const;
	template<typename T> T get() const
	{
		return convert::from_string<T>(get());
	}
	template<> array get<array>() const;
	template<> bool get<bool>() const;

	bool is_array() const;
	bool empty() const;

	value& operator[](const std::string& key);

private:
	class impl;
	std::shared_ptr<impl> pimpl;
};

}

}