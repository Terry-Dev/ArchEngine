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

#include <arch/utility.h>
#include <arch/string/charset.h>

#ifdef ARCHENGINE_PLATFORM_WINDOWS

#include <Windows.h>

namespace arch
{

namespace charset
{

std::string narrow(const std::wstring& _widen)
{
	// wchat_t to char
	std::string narrow;
	const int size = WideCharToMultiByte(CP_ACP, 0, _widen.data(), -1, NULL, 0, NULL, NULL);
	narrow.resize(size);
	WideCharToMultiByte(CP_ACP, 0, _widen.data(), _widen.size(), &narrow[0], narrow.size(), NULL, NULL);
	return std::move(narrow);
}

std::wstring widen(const std::string& narrow)
{
	// chat to wchar_t
	std::wstring widen;
	const int size = MultiByteToWideChar(CP_ACP, 0, narrow.data(), -1, NULL, 0) - 1;
	widen.resize(size);
	MultiByteToWideChar(CP_ACP, 0, narrow.data(), narrow.size(), &widen[0], widen.size());
	return std::move(widen);
}

}

}

#elif ARCHENGINE_PLATFORM_OSX

#include <CoreFoundation/CFString.h>

namespace arch
{

namespace charset
{

std::string narrow(const std::wstring& _widen)
{
	// wchat_t to char
	std::string narrow;
	CFStringRef cf_widen = CFStringCreateWithBytes(kCFAllocatorDefault, reinterpret_cast<const UInt8*>(_widen.data()), _widen.size() * sizeof(wchar_t), kCFStringEncodingUTF8, false);
	size_t size = CFStringGetMaximumSizeForEncoding(CFStringGetLength(cf_widen), kCFStringEncodingWindowsLatin1);
	narrow.resize(size);
	CFStringGetCString(cf_widen, &narrow[0], narrow.size() * sizeof(char), kCFStringEncodingWindowsLatin1);
	return std::move(narrow);
}

std::wstring widen(const std::string& _narrow)
{
	// chat to wchar_t
	std::wstring widen;
	CFStringRef cf_narrow = CFStringCreateWithBytes(kCFAllocatorDefault, reinterpret_cast<const unsigned char*>(_narrow.data()), _narrow.size() * sizeof(char), kCFStringEncodingUTF8, false);
	const size_t size = CFStringGetMaximumSizeForEncoding(CFStringGetLength(cf_narrow), kCFStringEncodingUTF8);
	widen.resize(size);
	CFStringGetCString(cf_narrow, reinterpret_cast<char*>(&widen[0]), widen.size() * sizeof(wchar_t), kCFStringEncodingUTF8);
	return std::move(widen);
}

}

}

#elif ARCHENGINE_PLATFORM_LINUX


#endif