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

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

namespace arch
{

inline int to_integer(const std::string& s)
{
	return std::stoi(s.c_str());
}

inline long to_long(const std::string& s)
{
	return std::stol(s.c_str());
}

inline unsigned long to_unsigned_long(const std::string& s)
{
	return std::stoul(s.c_str());
}

inline long long to_long_long(const std::string& s)
{
	return std::stoll(s.c_str());
}

inline unsigned long long to_unsigned_long_long(const std::string& s)
{
	return std::stoull(s.c_str());
}

inline float to_float(const std::string& s)
{
	return std::stof(s.c_str());
}

inline double to_double(const std::string& s)
{
	return std::stod(s.c_str());
}

inline std::string to_string(short value)
{
	return std::to_string(value);
}

inline std::string to_string(unsigned short value)
{
	return std::to_string(value);
}

inline std::string to_string(int value)
{
	return std::to_string(value);
}

inline std::string to_string(unsigned int value)
{
	return std::to_string(value);
}

inline std::string to_string(long value)
{
	return std::to_string(value);
}

inline std::string to_string(unsigned long value)
{
	return std::to_string(value);
}

inline std::string to_string(float value)
{
	return std::to_string(value);
}

inline std::string to_string(double value)
{
	return std::to_string(value);
}

template<typename type> inline std::string to_string(const type& _value)
{
	std::stringstream s;
	s << _value;
	return s.str();
}

inline std::string& to_upper(std::string& _str)
{
	std::transform(_str.begin(), _str.end(), _str.begin(), ::toupper);
	return _str;
}

inline std::string& to_lower(std::string& _str)
{
	std::transform(_str.begin(), _str.end(), _str.begin(), ::tolower);
	return _str;
}

inline std::vector<std::string> split(const std::string& _string, char _delimiter)
{
	std::vector<std::string> container;
	std::string part;
	std::istringstream isstream(_string);
	while (std::getline(isstream, part, _delimiter))
	{
		container.push_back(part);
	}
	return std::move(container);
}

inline std::vector<std::string> split(const std::string& _string, const std::string& _delimiter)
{
	std::vector<std::string> container;
	std::string part;
	size_t current = 0;
	size_t next;
	while ((next = _string.find(_string, current)) != std::string::npos)
	{
		container.push_back(std::string(_string, current, next - current));
		current = next + _delimiter.size();
	}
	container.push_back(std::string(_string, current, next - current));
	return std::move(container);
}

inline std::string join(const std::vector<std::string>& _strings, const std::string& _delimiter)
{
	std::string result;
	for (auto& s : _strings)
	{
		result += s;
	}
	return std::move(result);
}

template<class type> inline std::string format(type _value)
{
	return to_string(_value);
}

template<class type, class... args> inline std::string format(type _first, args... _value)
{
	return format(_first) + format(_value...);
}

}