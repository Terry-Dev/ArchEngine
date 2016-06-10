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

namespace arch
{

namespace ipv4
{

class address
{
public:
	address() = default;
	
	constexpr address(unsigned char _a, unsigned char _b, unsigned char _c, unsigned char _d)
		: a(_a), b(_b), c(_c), d(_d)
	{
	}

	~address() = default;


	std::string to_string() const
	{
		std::stringstream ss;
		ss << static_cast<int>(a) << '.' << static_cast<int>(b) << '.' << static_cast<int>(c) << '.' << static_cast<int>(d);
		return ss.str();
	}
	
	static constexpr address broadcast()
	{
		return{ 255, 255, 255, 255 };
	}

	static constexpr address loopback()
	{
		return{ 127, 0, 0, 1 };
	}

public:
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
};

}

}