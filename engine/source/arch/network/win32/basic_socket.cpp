#pragma comment(lib,"ws2_32.lib")
#include <network/basic_socket.hpp>
#include <winsock2.h>

using namespace arch;

class basic_socket::impl
{
public:
	impl()
	{
		WSADATA wsaData;
		int initErr = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (initErr == 0)
		{
			return;
		}
		switch (initErr)
		{
		default:
			break;
		}
	}
	~impl()
	{
		WSACleanup();
	}
};

basic_socket::basic_socket()
	:m_impl(new impl())
{
	logging("Constructor", "Initialized.", trace_level::debug);
};
basic_socket::~basic_socket()
{
	logging("Constructor", "Finalize.", trace_level::debug);
}
