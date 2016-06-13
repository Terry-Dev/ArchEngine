#pragma once

#include <memory>
#include "basic_network.h"

namespace arch
{

class socket
{
public:
	virtual ~socket() = default;
	virtual bool start() const = 0;
	virtual bool accept() const = 0;
	virtual bool send(const std::string& data) const = 0;
	virtual bool receive(std::string& result) const = 0;
	virtual void close() const = 0;
};

}