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
#include <memory>

class csv_reader final
{
public:
	csv_reader();
	csv_reader(const std::string& _path);
	csv_reader(const void* _data, size_t _size);
	~csv_reader();

	uint32_t rows() const;
	uint32_t columns(uint32_t _rows) const;

	std::string get(uint32_t _rows, uint32_t _columns) const;
	
	template<typename T> T get(uint32_t _rows, uint32_t _columns) const
	{
		std::stringstream ss;
		ss.str(get(_rows, _columns));
		T value;
		ss >> value;
		return value;
	}

private:
	class impl;
	std::shared_ptr<impl> pimpl;
};