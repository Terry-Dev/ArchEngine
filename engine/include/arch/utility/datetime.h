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

#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

namespace arch
{

class datetime
{
public:
	datetime() = default;

	datetime(int _year, int _month, int _day, int _hour, int _minute, int _second)
		: year(_year), month(_month), day(_day), hour(_hour), minute(_minute), second(_second)
	{
	}

	datetime(const datetime& time)
		: year(time.year), month(time.month), day(time.day), hour(time.hour), minute(time.minute), second(time.second)
	{
	}

	~datetime() = default;

#ifdef ARCHENGINE_PLATFORM_WINDOWS
	static datetime now()
	{
		std::time_t timer;
		std::tm local_time;

		std::time(&timer);
		localtime_s(&local_time, &timer);

		datetime now_datetime;

		now_datetime.year = local_time.tm_year + 1900;
		now_datetime.month = local_time.tm_mon + 1;
		now_datetime.day = local_time.tm_mday;
		now_datetime.hour = local_time.tm_hour;
		now_datetime.minute = local_time.tm_min;
		now_datetime.second = local_time.tm_sec;

		return std::move(now_datetime);
	}
#else
	static datetime now()
	{
		std::time_t timer;
		std::tm local_time;

		std::time(&timer);
		local_time = *std::localtime_r(&timer);

		date_time now_datetime;

		now_datetime.year = local_time.tm_year + 1900;
		now_datetime.month = local_time.tm_mon + 1;
		now_datetime.day = local_time.tm_mday;
		now_datetime.hour = local_time.tm_hour;
		now_datetime.minute = local_time.tm_min;
		now_datetime.second = local_time.tm_sec;

		return std::move(now_datetime);
	}
#endif

	std::string	to_string() const
	{
		std::stringstream ss;
		ss << year;
		ss << '/' << std::setw(2) << std::setfill('0') << month;
		ss << '/' << std::setw(2) << std::setfill('0') << day;
		ss << ' ' << std::setw(2) << std::setfill('0') << hour;
		ss << ':' << std::setw(2) << std::setfill('0') << minute;
		ss << ':' << std::setw(2) << std::setfill('0') << second;
		return ss.str();
	}

	std::string to_short_date_string() const
	{
		std::stringstream ss;
		ss << year;
		ss << '/' << std::setw(2) << std::setfill('0') << month;
		ss << '/' << std::setw(2) << std::setfill('0') << day;
		return ss.str();
	}

	std::string to_long_date_string() const
	{
		std::stringstream ss;
		ss << year << "年";
		ss << std::setw(2) << std::setfill('0') << month << "月";
		ss << std::setw(2) << std::setfill('0') << day << "日";
		return ss.str();
	}

	std::string to_short_time_string() const
	{
		std::stringstream ss;
		ss << std::setw(2) << std::setfill('0') << hour;
		ss << ':' << std::setw(2) << std::setfill('0') << minute;
		return ss.str();
	}

	std::string to_long_time_string() const
	{
		std::stringstream ss;
		ss << std::setw(2) << std::setfill('0') << hour;
		ss << ':' << std::setw(2) << std::setfill('0') << minute;
		ss << ':' << std::setw(2) << std::setfill('0') << second;
		return ss.str();
	}

	datetime& operator=(const datetime& time)
	{
		year = time.year;
		month = time.month;
		day = time.day;
		hour = time.hour;
		minute = time.minute;
		second = time.second;
		return *this;
	}

public:
	int	year;	///< 年
	int	month;	///< 月
	int	day;	///< 日
	int	hour;	///< 時
	int	minute;	///< 分
	int	second;	///< 秒
};

}
