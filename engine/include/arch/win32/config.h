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

#include "../arch/cross_compile.h"

#ifdef ARCHENGINE_PLATFORM_WINDOWS
#pragma comment (linker, "/entry:\"WinMainCRTStartup\"")
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib,"ArchEngine_x64_Debug.lib")
#else
#pragma comment(lib,"ArchEngine_x64.lib")
#endif
#elif _WIN32
#ifdef _DEBUG
#pragma comment(lib,"ArchEngine_x86_Debug.lib")
#else
#pragma comment(lib,"ArchEngine_x86.lib")
#endif
#endif
#endif