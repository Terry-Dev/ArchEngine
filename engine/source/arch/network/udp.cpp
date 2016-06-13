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

#include <arch/utility.h>
#include <arch/network/basic_network.h>
#include <arch/network/udp.h>

using namespace arch;

class udp::impl
{
public:
	impl();
	void set_address(int port, const std::string& address);
	bool send(const std::string& data);
	bool receive(std::string& result);
	bool start();
	~impl();

private:
	basic_network socket;
	bool is_server = false;
};

udp::udp()
: pimpl(std::make_shared<impl>())
{

}
udp::udp(int port, const std::string& address)
: pimpl(std::make_shared<impl>())
{
	pimpl->set_address(port, address);
}
udp::udp(const udp& udp)
: pimpl(udp.pimpl)
{
}
bool udp::start() const
{
	return pimpl->start();
}
bool udp::accept() const
{
	return true;
}
void udp::close() const
{
}
bool udp::send(const std::string& data) const
{
	return pimpl->send(data);
}
bool udp::receive(std::string& result) const
{
	return pimpl->receive(result);
}


udp::impl::impl()
: socket(basic_network::address_family::ipv4, basic_network::socket_type::dgram, basic_network::protocol::udp)
{
	socket.set_non_blocking();
}
udp::impl::~impl()
{
	socket.close_socket();
}
void udp::impl::set_address(int port, const std::string& address)
{
	socket.set_address(port, address);
	is_server = (address.empty());
}
bool udp::impl::start()
{
	if (!is_server)
	{
		return socket.bind_socket();
	}
	return true;
}
bool udp::impl::send(const std::string& data)
{
	return socket.send_socket(data.data(), data.size());
}
bool udp::impl::receive(std::string& data)
{
	if (socket.is_received_data())
	{
		char buff[100] = {};
		data = "";
		int len = 0;
		do
		{
			len = socket.receive(buff, 64);
			data += buff;
		} while (len <= 0 || len == -1);
		return true;
	}
	return false;
}