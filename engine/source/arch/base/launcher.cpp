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

#include "arch/cross_compile.h"
#include "win32/config.h"


//using namespace arch;

void arch_main();

#ifdef ARCHENGINE_PLATFORM_WINDOWS

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	arch_main();
	return 0;
}

#elif ARCHENGINE_PLATFORM_OSX

int main()
{
	arch_main();
	return 0;
}

#endif