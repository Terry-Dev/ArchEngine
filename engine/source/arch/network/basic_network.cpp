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
#include <arch/string.h>
#include <arch/network/basic_network.h>

#ifdef ARCHENGINE_PLATFORM_WINDOWS

#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace arch;

class basic_network::impl
{
public:
	impl();
	~impl();
	void initialize(basic_network::address_family family, basic_network::socket_type type, basic_network::protocol proto);

	bool is_received_data();

	bool set_address(int port, const std::string& address);

	bool connect_socket();
	bool m_listen(int back_log);
	bool m_bind();

	bool accept_socket();

	bool send_socket(const void* data, size_t length);

	int receive(void* out, int length);

	void set_non_blocking(bool flag);

	void close_socket();

private:

	SOCKET m_main_sock;
	SOCKET m_client_sock;
	//sockaddr_in address;
	sockaddr_in m_client;
	addrinfo m_address;
	sockaddr_in m_addr;
	addrinfo *m_res = nullptr;
	int m_last_error;
};

/*
	<< Base class caller >>
	*/


basic_network::basic_network(basic_network::address_family family, basic_network::socket_type type, basic_network::protocol proto)
: pimpl(std::make_shared<impl>())
{
	pimpl->initialize(family, type, proto);
}
basic_network::basic_network(const basic_network& basic_network)
: pimpl(basic_network.pimpl)
{

}
basic_network::~basic_network()
{

}
bool basic_network::set_address(int port, const std::string& addr)
{
	return pimpl->set_address(port, addr);
}
bool basic_network::connect_socket()
{
	return pimpl->connect_socket();
}
bool basic_network::bind_socket()
{
	return pimpl->m_bind();
}
bool basic_network::listen_socket(int backLog)
{
	return pimpl->m_listen(backLog);
}
bool basic_network::send_socket(const void* data, size_t length)
{
	return pimpl->send_socket(data, length);
}
void basic_network::set_non_blocking(bool flag)
{
	pimpl->set_non_blocking(flag);
}
int basic_network::receive(void* out, int length)
{
	return pimpl->receive(out, length);
}
bool basic_network::is_received_data()
{
	return pimpl->is_received_data();
}
bool basic_network::accept_socket()
{
	return pimpl->accept_socket();
}
void basic_network::close_socket()
{
	pimpl->close_socket();
}

/*
	<< impl main function >>
	*/

//
basic_network::impl::impl()
{

}
basic_network::impl::~impl()
{
	if (m_res != nullptr)
	{
		freeaddrinfo(m_res);
	}
	closesocket(m_main_sock);
	close_socket();
	WSACleanup();
}

void basic_network::impl::initialize(basic_network::address_family family, basic_network::socket_type type, basic_network::protocol proto)
{
	static const int address_famiry_table[] = { AF_UNSPEC, AF_UNIX, AF_INET, AF_INET6 };
	static const int sock_type_table[] = { SOCK_STREAM, SOCK_DGRAM, SOCK_RAW, SOCK_RDM, SOCK_SEQPACKET };
	static const int protocol_table[] = { 0, IPPROTO_ICMP, IPPROTO_IGMP, 3, IPPROTO_TCP, IPPROTO_UDP, IPPROTO_ICMPV6 };
	WSAData data;
	int wsa_result = WSAStartup(MAKEWORD(2, 2), &data);
	if (wsa_result == 0)
	{
		memset(&this->m_address, 0, sizeof(this->m_address));
		m_address.ai_family = address_famiry_table[static_cast<int>(family)];
		m_address.ai_socktype = sock_type_table[static_cast<int>(type)];
		m_address.ai_protocol = protocol_table[static_cast<int>(proto)];
		m_main_sock = socket(m_address.ai_family, m_address.ai_socktype, m_address.ai_protocol);
		if (m_main_sock == INVALID_SOCKET)
		{
			logging::error("::network::basic_network : Socket create error.");
		}
		else
		{
			logging::error("::network::basic_network : Initialize complite.");
		}
	}
	else
	{
		logging::error("::network::basic_network : Initialize error.");
		m_last_error = wsa_result;
	}
}
bool basic_network::impl::set_address(int port, const std::string& address)
{
	if (!address.empty())
	{
		//addrinfo *res;
		if (getaddrinfo(address.c_str(), std::::to_string(port).data(), &this->m_address, &m_res) != 0)
		{
			logging::error("::network::basic_network : This address is't ip or Don't find address for Domain Name Server.");
			return false;
		}
		this->m_address = *m_res;
		//freeaddrinfo(res);
		logging::debug("::network::basic_network : Set address as Client.");
	}
	else
	{
		m_addr.sin_addr.S_un.S_addr = INADDR_ANY;
		m_addr.sin_port = htons(port);
		m_addr.sin_family = this->m_address.ai_family;
		this->m_address.ai_addr = reinterpret_cast<sockaddr*>(&m_addr);
		this->m_address.ai_addrlen = sizeof(m_addr);
		bool yes = true;
		setsockopt(m_main_sock, SOL_SOCKET, SO_REUSEADDR | SO_BROADCAST, reinterpret_cast<const char*>(&yes), sizeof(yes));
		logging::debug("::network::basic_network : Set address as Server.");
	}
	return true;
}
bool basic_network::impl::connect_socket()
{
	size_t result = connect(m_main_sock, static_cast<sockaddr*>(m_address.ai_addr), static_cast<int>(m_address.ai_addrlen));
	m_client_sock = m_main_sock;
	if (result != SOCKET_ERROR)
	{
		logging::debug("::network::basic_network : Connection success.");
		return true;
	}
	else
	{
		m_last_error = WSAGetLastError();
		if (m_last_error == WSAEISCONN)
		{
			return true;
		}
		else if (m_last_error == WSAEALREADY)
		{

		}
		else if (m_last_error == WSAEWOULDBLOCK)
		{
			return true;
		}
		else
		{
			logging::error("::network::basic_network : Connection error.");
			logging::error(convert::to_string(m_last_error));
		}
	}
	return false;
}
bool basic_network::impl::m_bind()
{
	size_t result = bind(m_main_sock, m_address.ai_addr, static_cast<int>(m_address.ai_addrlen));
	if (result != 0)
	{
		m_last_error = static_cast<int>(result);
		logging::error("::network::basic_network : Binding error(" + convert::to_string(WSAGetLastError()) + ")");
		return false;
	}
	logging::debug("::network::basic_network : Binding success.");
	return true;
}
bool basic_network::impl::m_listen(int back_log)
{
	int result = -1;
	result = listen(m_main_sock, back_log);
	if (result == 0)
	{
		logging::debug("::network::basic_network : Listening...");
		return true;
	}
	m_last_error = WSAGetLastError();
	logging::error("::network::basic_network : Listen error");
	return false;
}
bool basic_network::impl::send_socket(const void* data, size_t length)
{
	int result = 0;
	switch (this->m_address.ai_socktype)
	{
	case SOCK_DGRAM:
		result = sendto(m_main_sock, reinterpret_cast<const char*>(data), length, 0, m_address.ai_addr, sizeof(*m_address.ai_addr));
		break;
	default:
		result = send(m_client_sock, reinterpret_cast<const char*>(data), length, 0);
		break;
	}
	if (result == length)
	{
		logging::debug(":network::basic_network : Send Data.");
		return true;
	}
	m_last_error = WSAGetLastError();
	return false;
}
void basic_network::impl::set_non_blocking(bool flag)
{
	u_long val = (flag ? 1 : 0);
	logging::debug("::network::basic_network : Change Non Blocking flag : " + std::to_string(flag));
	ioctlsocket(m_main_sock, FIONBIO, &val);
}
int basic_network::impl::receive(void* out, int length)
{
	char* result = reinterpret_cast<char*>(out);
	int outlen = recv(m_client_sock, result, length, 0);
	m_last_error = WSAGetLastError();
	if (outlen > 0 && outlen != SOCKET_ERROR)
	{
		out = result;
		logging::debug("::network::basic_network : Recive data. : " + std::to_string(outlen));
		return outlen;
	}
	else if (outlen == 0)
	{
		if (WSAGetLastError() == WSAENOTCONN)
		{
			logging::debug("::network::basic_network : Connection Closed.");
		}
		return 0;
	}
	else
	{
		if (m_last_error == WSAEWOULDBLOCK)
		{
			logging::debug("::network::basic_network : Would blocking. wait.");
		}
		else
		{
			logging::error("::network::basic_network : Known error.");
		}
		return -1;
	}
	return -1;
}
bool basic_network::impl::is_received_data()
{
	char a;
	int ll = 0;
	int l;
	l = recv(m_client_sock, &a, 1, MSG_PEEK);
	if (l > 0)
	{
		return true;
	}
	else
	{
		m_last_error = WSAGetLastError();
	}
	return false;
}
bool basic_network::impl::accept_socket()
{
	int len = sizeof(m_client);
	m_client_sock = accept(m_main_sock, reinterpret_cast<sockaddr*>(&m_client), &len);
	if (m_client_sock != INVALID_SOCKET)
	{
		logging::debug("::network::basic_network : Connection start.");
		return true;
	}
	return false;
}
void basic_network::impl::close_socket()
{
	shutdown(m_client_sock, SD_SEND);
	while (is_received_data())
	{
		char buff[64];
		receive(buff, 64);
	}
	shutdown(m_client_sock, SD_RECEIVE);
	closesocket(m_client_sock);
	logging::debug("::network::basic_network : Connection close.");
}

#elif ARCHENGINE_PLATFORM_OSX

#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"
#include "sys/ioctl.h"
#include "netdb.h"

using namespace arch;

class basic_network::impl {
public:
	impl();
	~impl();
	void initialize(basic_network::address_family family, basic_network::socket_type type, basic_network::protocol proto);

	bool is_received_data();

	bool set_address(int port, const u8string& address);

	bool connect_socket();
	bool m_listen(int back_log);
	bool m_bind();

	bool accept_socket();

	bool send_socket(const void* data, uint length);

	int get_receive(void* out, int length);

	void set_non_blocking(bool flag);

	void close_socket();

private:

	int m_main_sock = 0;
	int m_client_sock;
	//sockaddr_in address;
	sockaddr_in m_client;
	addrinfo m_address;
	sockaddr_in m_addr;
	addrinfo *m_res = nullptr;
	int m_last_error;
};

basic_network::basic_network(basic_network::address_family family, basic_network::socket_type type, basic_network::protocol protocol)
	: pimpl(std::make_shared<impl>())
{
	pimpl->initialize(family, type, protocol);
}
basic_network::basic_network(const basic_network &basic_network)
	: pimpl(basic_network.pimpl)
{

}
basic_network::~basic_network() {}

bool basic_network::set_address(int port, const u8string& address)
{
	return pimpl->set_address(port, address);
}
bool basic_network::is_received_data()
{
	return pimpl->is_received_data();
}
bool basic_network::connect_socket()
{
	return pimpl->connect_socket();
}
bool basic_network::bind_socket()
{
	return pimpl->m_bind();
}
bool basic_network::listen_socket(int back_log)
{
	return pimpl->m_listen(back_log);
}
bool basic_network::accept_socket()
{
	return pimpl->accept_socket();
}
bool basic_network::send_socket(const void* data, uint length)
{
	return pimpl->send_socket(data, length);
}
int basic_network::get_receive(void* out, int length)
{
	return pimpl->get_receive(out, length);
}
void basic_network::set_non_blocking(bool flag)
{
	pimpl->set_non_blocking(flag);
}
void basic_network::close_socket()
{
	pimpl->close_socket();
}

basic_network::impl::impl()
{

}
basic_network::impl::~impl()
{

}
void basic_network::impl::initialize(basic_network::address_family family, basic_network::socket_type type, basic_network::protocol proto)
{
	static const int address_famiry_table[] = { AF_UNSPEC, AF_UNIX, AF_INET, AF_INET6 };
	static const int sock_type_table[] = { SOCK_STREAM, SOCK_DGRAM, SOCK_RAW, SOCK_RDM, SOCK_SEQPACKET };
	static const int protocol_table[] = { 0, IPPROTO_ICMP, IPPROTO_IGMP, 3, IPPROTO_TCP, IPPROTO_UDP, IPPROTO_ICMPV6 };

	memset(&this->m_address, 0, sizeof(this->m_address));
	m_address.ai_family = address_famiry_table[static_cast<int>(family)];
	m_address.ai_socktype = sock_type_table[static_cast<int>(type)];
	m_address.ai_protocol = protocol_table[static_cast<int>(proto)];

	m_main_sock = socket(m_address.ai_family, m_address.ai_socktype, m_address.ai_protocol);
	if (m_main_sock < 0)
	{
		logging::error("::network::basic_network : Socket create error.");
	}
	else
	{
		logging::infomation("::network::basic_network : Initialize complite.");
	}
}
bool basic_network::impl::set_address(int port, const u8string& address)
{
	if (!address.empty())
	{
		if (getaddrinfo(charset::to_ansi(address).data(), convert::to_string(port).data()/*convert::to_string(port).data()*/, &this->m_address, &m_res) != 0)
		{
			logging::error("::network::basic_network : This address is't ip or Don't find address for Domain Name Server.");
			return false;
		}
		this->m_address = *m_res;
		logging::debug("::network::basic_network : Set address as Client.");
	}
	else
	{
		m_addr.sin_addr.s_addr = INADDR_ANY;
		m_addr.sin_port = htons(port);
		m_addr.sin_family = this->m_address.ai_family;
		this->m_address.ai_addr = reinterpret_cast<sockaddr*>(&m_addr);
		this->m_address.ai_addrlen = sizeof(m_addr);
		bool yes = true;
		setsockopt(m_main_sock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&yes), sizeof(yes));
		logging::debug("::network::basic_network : Set address as Server.");
	}
	return true;
}
bool basic_network::impl::connect_socket()
{
	int result = connect(m_main_sock, static_cast<sockaddr*>(m_address.ai_addr), m_address.ai_addrlen);
	m_client_sock = m_main_sock;
	if (result == 0)
	{
		logging::debug("::network::basic_network : Connection success.");
		return true;
	}
	else
	{
		m_last_error = errno;//GetLastError();
		if (m_last_error == EISCONN)
		{
			return true;
		}
		else if (m_last_error == EALREADY)
		{

		}
		else if (m_last_error == EWOULDBLOCK)
		{
			return true;
		}
		else
		{
			logging::error("::network::basic_network : Connection error.");
			logging::error(convert::to_string(m_last_error));
		}
	}
	return false;
}
bool basic_network::impl::m_bind()
{
	size_t result = bind(m_main_sock, m_address.ai_addr, m_address.ai_addrlen);
	if (result != 0)
	{
		m_last_error = errno;
		logging::error("::network::basic_network : Binding error(" + convert::to_string(errno) + ")");
		return false;
	}
	logging::debug("::network::basic_network : Binding success.");
	return true;
}
bool basic_network::impl::m_listen(int back_log)
{
	int result = -1;
	result = listen(m_main_sock, back_log);
	if (result == 0)
	{
		logging::debug("::network::basic_network : Listening...");
		return true;
	}
	m_last_error = errno;//WSAGetLastError();
	logging::error("::network::basic_network : Listen error");
	return false;
}
bool basic_network::impl::send_socket(const void* data, uint length)
{
	int result = 0;
	switch (this->m_address.ai_family)
	{
	case SOCK_DGRAM:
		result = sendto(m_main_sock, reinterpret_cast<const char*>(data), length, 0, m_address.ai_addr, sizeof(*m_address.ai_addr));
		break;
	default:
		result = send(m_client_sock, reinterpret_cast<const char*>(data), length, 0);
		break;
	}
	if (result == length)
	{
		logging::debug(":network::basic_network : Send Data.");
		return true;
	}
	m_last_error = errno;//WSAGetLastError();
	return false;
}
void basic_network::impl::set_non_blocking(bool flag)
{
	u_long val = (flag ? 1 : 0);
	logging::debug("::network::basic_network : Change Non Blocking flag : " + convert::to_string(flag));
	ioctl(m_main_sock, FIONBIO, &val);
}
int basic_network::impl::get_receive(void* out, int length)
{
	char* result = reinterpret_cast<char*>(out);
	int outlen = recv(m_client_sock, result, length, 0);
	m_last_error = errno;//WSAGetLastError();
	if (outlen > 0)
	{
		out = result;
		logging::debug("::network::basic_network : Recive data. : " + convert::to_string(outlen));
		return outlen;
	}
	else if (outlen == 0)
	{
		if (errno == ENOTCONN)
		{
			logging::debug("::network::basic_network : Connection Closed.");
		}
		return 0;
	}
	else
	{
		if (m_last_error == EWOULDBLOCK)
		{
			logging::debug("::network::basic_network : Would blocking. wait.");
		}
		else
		{
			logging::error("::network::basic_network : Known error.");
		}
		return -1;
	}
	return -1;
}
bool basic_network::impl::is_received_data()
{
	char a;
	int ll = 0;
	int l;
	do
	{
		l = recv(m_client_sock, &a, 1, MSG_PEEK);
	} while (l == 0);
	if (l > 0)
	{
		return true;
	}
	else
	{
		m_last_error = errno;
	}
	return false;
}
bool basic_network::impl::accept_socket()
{
	socklen_t len = sizeof(m_client);
	m_client_sock = accept(m_main_sock, reinterpret_cast<sockaddr*>(&m_client), &len);
	if (m_client_sock != -1)
	{
		logging::debug("::network::basic_network : Connection start.");
		return true;
	}
	m_last_error = errno;
	return false;
}
void basic_network::impl::close_socket()
{
	shutdown(m_client_sock, SHUT_RDWR);
	close(m_client_sock);
	logging::debug("::network::basic_network : Connection close.");
}

#endif