#pragma once

#include <memory>
#include <functional>
#include <string>

namespace arch
{

namespace win32
{

class module
{
public:
	module();
	module(const module& module);
	module(module&& module);
	module(const std::string& path);
	~module();
	
	void	close();
	void*	function(const char* functionName) const;

	template<typename T> T function(const char* function_name) const
	{
		return reinterpret_cast<T>(function(function_name));
	}

	bool	is_opened() const;
	bool	operator!() const;

	module& operator=(const module& module);
	module& operator=(module&& module);

private:
	class impl;
	std::shared_ptr<impl> pimpl;
};

}

}