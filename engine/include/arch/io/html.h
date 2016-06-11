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

#include "logging.h"
#include "text_file.h"

namespace arch
{

class html_logger final : public logger
{
public:
	html_logger();
	html_logger(const std::string& _path = "log.html");
	~html_logger();

	void write(const std::string& message, trace_level level) override;

private:
	text_writer writer;
};

}