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

namespace arch
{
	
namespace constant
{

///< e
template<typename type> inline constexpr type e()
{
	return static_cast<type>(2.71828182845904523536);
}

///< ƒÎ
template<typename type> inline constexpr type pi()
{
	return static_cast<type>(3.14159265358979323846);
}

template<typename type> inline constexpr type two_pi()
{
	return static_cast<type>(6.28318530717958647692);
}

template<typename type> inline constexpr type half_pi()
{
	return static_cast<type>(1.57079632679489661923);
}

template<typename type> inline constexpr type light_speed()
{
	return static_cast<type>(2.99792458e8);
}

template<typename type> inline constexpr type standard_gravity()
{
	return static_cast<type>(9.80665);
}

template<typename type> inline constexpr type apery()
{
	return static_cast<type>(1.20205690315959428540);
}

template<typename type> inline constexpr type planck()
{
	return static_cast<type>(6.626070040e-34);
}

template<typename type> inline constexpr type dirac()
{
	return static_cast<type>(1.054571800e-34);
}

template<typename type> inline constexpr type glaisher_kinkelin()
{
	return static_cast<type>(1.28242712910062263688);
}

template<typename type> inline constexpr type catalan()
{
	return static_cast<type>(0.91596559417721901505);
}

}

}