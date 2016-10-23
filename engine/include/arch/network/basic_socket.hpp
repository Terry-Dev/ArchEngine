//=================================================================================//
//                                                                                 //
//  ArchEngine                                                                     //
//                                                                                 //
//  Copyright (C) 2011-2016 Surigoma                                               //
//                                                                                 //
//  This file is a portion of the ArchEngine. It is distributed under the MIT      //
//  License, available in the root of this distribution and at the following URL.  //
//  http://opensource.org/licenses/mit-license.php                                 //
//                                                                                 //
//=================================================================================//

#pragma once

#include <memory>
#include <string>
#include <network/ipv4.h>
#include <logger/logging.h>

using namespace arch;

namespace arch
{
class basic_socket
{
private:
	class impl;
	std::unique_ptr<impl> m_impl;
	void logging(std::string function_name, std::string log_message, trace_level level)
	{
		static const std::string class_name = "basic_network";
		switch (level)
		{
		case arch::trace_level::critical:
			logging::critical(log_message, function_name, class_name);
			return;
		case arch::trace_level::error:
			logging::error(log_message, function_name, class_name);
			return;
		case arch::trace_level::warning:
			logging::warning(log_message, function_name, class_name);
			return;
		case arch::trace_level::infomation:
			logging::infomation(log_message, function_name, class_name);
			return;
		case arch::trace_level::debug:
			logging::debug(log_message, function_name, class_name);
			return;
		default:
			break;
		}
	}

public:
	basic_socket();
	~basic_socket();
};
enum address_family : int
{
    INET,
    INET6,
    UNIX,
    LINK,
	BTH,
    UNSPEC
};
enum sock_type : int
{
    STREAM,
    DGRAM,
    RAW
};
}
