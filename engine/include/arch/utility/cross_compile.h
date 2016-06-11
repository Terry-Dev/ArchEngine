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

#ifdef _WIN32
#define ARCHENGINE_PLATFORM_WINDOWS
#elif _WIN64
#define ARCHENGINE_PLATFORM_WINDOWS
#elif __APPLE__
#define ARCHENGINE_PLATFORM_OSX
#elif __linux__
#define ARCHENGINE_PLATFORM_LINUX
#endif