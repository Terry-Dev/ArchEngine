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
#include <arch/string/codecvt.h>

using namespace arch;

#ifdef ARCHENGINE_PLATFORM_WINDOWS

#include <Windows.h>
#include <uchar.h>

std::string codecvt_ansi::from_ansi(const std::string& _ansi)
{
	return _ansi;
}

std::string codecvt_ansi::from_utf8(const std::string& _utf8)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
	std::wstring widen = cvt.from_bytes(_utf8);
	return std::move(charset::narrow(widen));
}

std::string codecvt_ansi::from_utf16le(const std::u16string& _utf16le)
{
	std::wstring widen;
	size_t size = _utf16le.size() / sizeof(wchar_t);
	widen.reserve(size);
	for (size_t i = 0; i < size; i += sizeof(wchar_t))
	{
		widen.push_back(reinterpret_cast<const wchar_t*>(_utf16le.data())[i]);
	}
	return std::move(charset::narrow(widen));
}

std::string codecvt_ansi::from_utf16be(const std::u16string& _utf16be)
{
	std::wstring widen;
	size_t size = _utf16be.size() / sizeof(wchar_t);
	widen.reserve(size);
	for (size_t i = 0; i < size; i += sizeof(wchar_t))
	{
		widen.push_back(endian_swap(reinterpret_cast<const wchar_t*>(_utf16be.data())[i]));
	}
	return std::move(charset::narrow(widen));
}

std::string codecvt_ansi::from_utf32le(const std::u32string& _utf32le)
{
	return std::string();
}

std::string codecvt_ansi::from_utf32be(const std::u32string& _utf32be)
{
	return std::string();
}


std::string codecvt_utf8::from_ansi(const std::string& _ansi)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
	return std::move(cvt.to_bytes(charset::widen(_ansi)));
}

std::string codecvt_utf8::from_utf8(const std::string& _utf8)
{
	return _utf8;
}

std::string codecvt_utf8::from_utf16le(const std::u16string& _utf16le)
{
	//*
	std::wstring_convert<std::codecvt_utf8_utf16<int16_t, 1114111UL, std::little_endian>, int16_t> cvt;
	auto pointer = reinterpret_cast<const int16_t*>(_utf16le.data());
	return std::move(cvt.to_bytes(pointer, pointer + _utf16le.size()));
	/*/
	VS2015の不具合で使用できない
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 1114111UL, std::little_endian>, char16_t> cvt;
	return std::move(cvt.to_bytes(_utf16le));
	//*/
}

std::string codecvt_utf8::from_utf16be(const std::u16string& _utf16be)
{
	//*
	std::wstring_convert<std::codecvt_utf8_utf16<int16_t, 1114111UL>, int16_t> cvt;
	auto pointer = reinterpret_cast<const int16_t*>(_utf16be.data());
	return std::move(cvt.to_bytes(pointer, pointer + _utf16be.size()));
	/*/
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 1114111UL>, char16_t> cvt;
	return std::move(cvt.to_bytes(_utf16be));
	//*/
}

std::string codecvt_utf8::from_utf32le(const std::u32string& _utf32le)
{
	//*
	std::wstring_convert<std::codecvt_utf8<int32_t, 1114111UL, std::little_endian>, int32_t> cvt;
	auto pointer = reinterpret_cast<const int32_t*>(_utf32le.data());
	return std::move(cvt.to_bytes(pointer, pointer + _utf32le.size()));
	/*/
	std::wstring_convert<std::codecvt_utf8<char32_t, 1114111UL, std::little_endian>, char32_t> cvt;
	return std::move(cvt.to_bytes(_utf32le));
	//*/
}

std::string codecvt_utf8::from_utf32be(const std::u32string& _utf32be)
{
	//*
	std::wstring_convert<std::codecvt_utf8<int32_t, 1114111UL>, int32_t> cvt;
	auto pointer = reinterpret_cast<const int32_t*>(_utf32be.data());
	return std::move(cvt.to_bytes(pointer, pointer + _utf32be.size()));
	/*/
	std::wstring_convert<std::codecvt_utf8<char32_t, 1114111UL>, char32_t> cvt;
	return std::move(cvt.to_bytes(_utf32be));
	//*/
}


std::u16string codecvt_utf16le::from_ansi(const std::string& _ansi)
{
	std::u16string utf16;
	const int size = MultiByteToWideChar(CP_ACP, 0, _ansi.data(), -1, NULL, 0) - 1;
	utf16.resize(size);
	MultiByteToWideChar(CP_ACP, 0, _ansi.data(), _ansi.size(), reinterpret_cast<wchar_t*>(&utf16[0]), size);
	return std::move(utf16);
}

std::u16string codecvt_utf16le::from_utf8(const std::string& _utf8)
{
	//*
	std::wstring_convert<std::codecvt_utf8_utf16<int16_t, 1114111UL, std::little_endian>, int16_t> cvt;
	auto int16string = cvt.from_bytes(_utf8);
	auto pointer = reinterpret_cast<const char16_t*>(int16string.data());
	return std::move(std::u16string(pointer, int16string.size()));
	/*/
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 1114111UL, std::little_endian>, char16_t> cvt;
	return std::move(cvt.from_bytes(_utf8));
	//*/
}

std::u16string codecvt_utf16le::from_utf16le(const std::u16string& _utf16le)
{
	return _utf16le;
}

std::u16string codecvt_utf16le::from_utf16be(const std::u16string& _utf16be)
{
	std::u16string utf16le;
	utf16le.reserve(_utf16be.size());
	for (char16_t c : _utf16be)
	{
		utf16le.push_back(endian_swap(c));
	}
	return std::move(utf16le);
}

std::u16string codecvt_utf16le::from_utf32le(const std::u32string& _utf32le)
{
	std::string utf8 = codecvt_utf8::from_utf32le(_utf32le);
	return std::move(codecvt_utf16le::from_utf8(utf8));
}

std::u16string codecvt_utf16le::from_utf32be(const std::u32string& _utf32be)
{
	std::string utf8 = codecvt_utf8::from_utf32be(_utf32be);
	return std::move(codecvt_utf16le::from_utf8(utf8));
}


std::u16string codecvt_utf16be::from_ansi(const std::string& _ansi)
{
	std::u16string utf16le = codecvt_utf16le::from_ansi(_ansi);
	return std::move(codecvt_utf16be::from_utf16le(utf16le));
}

std::u16string codecvt_utf16be::from_utf8(const std::string& _utf8)
{
	//*
	std::wstring_convert<std::codecvt_utf8_utf16<int16_t, 1114111UL>, int16_t> cvt;
	auto int16string = cvt.from_bytes(_utf8);
	auto pointer = reinterpret_cast<const char16_t*>(int16string.data());
	return std::move(std::u16string(pointer, int16string.size()));
	/*/
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 1114111UL>, char16_t> cvt;
	return std::move(cvt.from_bytes(_utf8));
	//*/
}

std::u16string codecvt_utf16be::from_utf16le(const std::u16string& _utf16le)
{
	std::u16string utf16be;
	utf16be.reserve(_utf16le.size());
	for (char16_t c : _utf16le)
	{
		utf16be.push_back(endian_swap(c));
	}
	return std::move(utf16be);
}

std::u16string codecvt_utf16be::from_utf16be(const std::u16string& _utf16be)
{
	return _utf16be;
}

std::u16string codecvt_utf16be::from_utf32le(const std::u32string& _utf32le)
{
	std::string utf8 = codecvt_utf8::from_utf32le(_utf32le);
	return std::move(codecvt_utf16be::from_utf8(utf8));
}

std::u16string codecvt_utf16be::from_utf32be(const std::u32string& _utf32be)
{
	std::string utf8 = codecvt_utf8::from_utf32be(_utf32be);
	return std::move(codecvt_utf16be::from_utf8(utf8));
}

#elif ARCHENGINE_PLATFORM_OSX

#elif ARCHENGINE_PLATFORM_LINUX

#endif