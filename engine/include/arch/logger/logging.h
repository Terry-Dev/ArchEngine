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

#include <string>
#include <memory>

namespace arch
{

enum class trace_level
{
	critical,
	error,
	warning,
	infomation,
	debug,
};

class logger
{
public:
	virtual ~logger() = default;
	virtual void write(const std::string& message, trace_level level) = 0;
};

class logging
{
public:
	static void reset()
	{
		return m_logger.reset();
	}

	template<class type, class... args> static type& set_logger(args... _args)
	{
		m_logger = std::make_shared<type>(_args...);
		return *m_logger.get();
	}

	static void set_trace_level(trace_level _level)
	{
		m_level = _level;
	}

	static trace_level get_trace_level()
	{
		return m_level;
	}

	static void write(const std::string& _message, trace_level _level)
	{
		if (m_level < _level || !m_logger)
		{
			return;
		}

		m_logger->write(_message, _level);
	}

	static void critical(const std::string& _message)
	{
		write(_message, trace_level::critical);
	}

	static void critical(const std::string& _message, const std::string& _function_name, const std::string& _class_name = "")
	{
		critical(_class_name + "::" + _function_name + " : " + _message);
	}

	static void error(const std::string& _message)
	{
		write(_message, trace_level::error);
	}

	static void error(const std::string& _message, const std::string& _function_name, const std::string& _class_name = "")
	{
		error(_class_name + "::" + _function_name + " : " + _message);
	}

	static void warning(const std::string& _message)
	{
		write(_message, trace_level::warning);
	}

	static void warning(const std::string& _message, const std::string& _function_name, const std::string& _class_name = "")
	{
		warning(_class_name + "::" + _function_name + " : " + _message);
	}

	static void infomation(const std::string& _message)
	{
		write(_message, trace_level::infomation);
	}

	static void infomation(const std::string& _message, const std::string& _function_name, const std::string& _class_name = "")
	{
		infomation(_class_name + "::" + _function_name + " : " + _message);
	}

	static void debug(const std::string& _message)
	{
		write(_message, trace_level::debug);
	}

	static void debug(const std::string& _message, const std::string& _function_name, const std::string& _class_name = "")
	{
		debug(_class_name + "::" + _function_name + " : " + _message);
	}

private:
	static trace_level m_level;
	static std::shared_ptr<logger> m_logger;
};

}