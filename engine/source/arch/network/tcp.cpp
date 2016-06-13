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
#include <arch/network/tcp.h>

using namespace arch;

class tcp::impl
{
public:
	impl();
	void set_address(int port, const std::string& address);
	bool start();
	bool accept();
	void close();
	bool send(const std::string& data);
	bool receive(std::string& result);
	~impl();

private:
	basic_network socket;
	bool is_server = false;
};

tcp::tcp()
: pimpl(std::make_shared<impl>())
{

}
tcp::tcp(int port, const std::string& address)
: pimpl(std::make_shared<impl>())
{
	pimpl->set_address(port, address);
}
tcp::tcp(const tcp& tcp)
: pimpl(tcp.pimpl)
{
}
bool tcp::start() const
{
	return pimpl->start();
}
bool tcp::accept() const
{
	return pimpl->accept();
}
void tcp::close() const
{
	pimpl->close();
}
bool tcp::send(const std::string& data) const
{
	return pimpl->send(data);
}
bool tcp::receive(std::string& result) const
{
	return pimpl->receive(result);
}


tcp::impl::impl()
: socket(basic_network::address_family::ipv4, basic_network::socket_type::stream, basic_network::protocol::tcp)
{
	socket.set_non_blocking();
}
tcp::impl::~impl()
{
	socket.close_socket();
}
bool tcp::impl::start()
{
	if (is_server)
	{
		return (socket.bind_socket() && socket.listen_socket(1));
	}
	else
	{
		return socket.connect_socket();
	}
}
void tcp::impl::set_address(int port, const std::string& address)
{
	socket.set_address(port, address);
	is_server = (address.empty());
}
bool tcp::impl::accept()
{
	return socket.accept_socket();
}
void tcp::impl::close()
{
	socket.close_socket();
}
bool tcp::impl::send(const std::string& data)
{
	return socket.send_socket(data.data(), data.size());
}
bool tcp::impl::receive(std::string& data)
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