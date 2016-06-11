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

#include <vector>
#include "types.h"

namespace arch
{

namespace io
{

bool is_file(const std::string& path);
bool is_directory(const std::string& path);

namespace file
{

bool exists(const std::string& path);
bool move(const std::string& path, const std::string& new_path);
bool copy(const std::string& path, const std::string& new_path);
bool remove(const std::string& path);

}

namespace directory
{

bool empty(const std::string& path);
bool create(const std::string& path);
bool exists(const std::string& path);
bool move(const std::string& path, const std::string& new_path);
bool copy(const std::string& path, const std::string& new_path);
bool remove(const std::string& path);

std::vector<std::string> enumerate_files(const std::string& path);
std::vector<std::string> enumerate_files(const std::string& path, const std::string& extension);
std::vector<std::string> enumerate_directories(const std::string& PathName);
std::vector<std::string> enumerate_files_and_directories(const std::string& PathName);

void set_current(const std::string& current_path);
std::string get_current();

}

}

}