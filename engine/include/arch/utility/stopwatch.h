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

#include <chrono>
#include <ratio>

namespace arch
{

class stopwatch
{
public:
	stopwatch(bool _is_starting = false)
		: m_is_starting(_is_starting)
	{
		if (m_is_starting)
		{
			m_start = std::chrono::high_resolution_clock::now();
		}
	}

	~stopwatch() = default;

	void start()
	{
		if (m_is_starting)
		{
			return;
		}

		m_start = std::chrono::high_resolution_clock::now();
		m_is_starting = true;
	}

	void restart()
	{
		m_start = std::chrono::high_resolution_clock::now();
		m_is_starting = true;
	}

	void stop()
	{
		m_is_starting = false;
	}

	template<class duration_type = std::chrono::duration<double, std::ratio<1, 1>>> duration_type elapsed() const
	{
		if (!m_is_starting)
		{
			return duration_type(static_cast<duration_type::rep>(0));
		}
		auto last = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<duration_type>(last - m_start);
	}

	bool is_starting() const
	{
		return m_is_starting;
	}

	bool is_stopped() const
	{
		return !is_starting();
	}

private:
	bool m_is_starting;
	std::chrono::high_resolution_clock::time_point m_start;
};

}