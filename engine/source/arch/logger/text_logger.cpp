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

#include <vector>
#include <arch/utility.h>
#include <arch/logger/text_logger.h>

using namespace arch;

text_logger::text_logger(const std::string& _path)
: logger()
{
	writer = text::writer(_path, open_mode::truncate, text_encoding::utf8);
	if (!writer)
	{
		return;
	}

	writer.write_line("ArchEngine Log");
}

text_logger::~text_logger()
{
	if (!writer)
	{
		return;
	}

	writer.write_line("ArchEngine Copyright (c) 2011-2015 60FPS*");
	writer.close();
}

void text_logger::write(const std::string& message, trace_level level)
{
	if (!writer)
	{
		return;
	}
	auto date = datetime::now();

	switch (level)
	{
	case trace_level::critical:
		writer.write_line(date.to_string() + "[Critical] " + message);
		break;
	case trace_level::error:
		writer.write_line(date.to_string() + "[Error] " + message);
		break;
	case trace_level::infomation:
		writer.write_line(date.to_string() + "[Infomation] " + message);
		break;
	case trace_level::debug:
		writer.write_line(date.to_string() + "[Debug] " + message);
		break;
	}
	writer.flush();
}