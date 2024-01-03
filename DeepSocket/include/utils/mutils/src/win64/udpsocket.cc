#include "../../udpsocket.h"

#include "wsa_support.h"

namespace mutils
{

udpSocket::udpSocket(const netAddress& local_address)
{
	if (local_address.version == 4)
	{
		_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}
	else if (local_address.version == 6)
	{
		_socket = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
	}
	else
	{
		throw "unsupported address";
	}

	if (bind(_socket, (SOCKADDR*)(local_address.__raw), local_address.addrlen) != 0)
		throw "failed to bind";
}

udpSocket::~udpSocket()
{
	closesocket(_socket);
}

int udpSocket::SendTo(const void* buf, size_t len, const netAddress& to_address)
{
	sendto(_socket, (const char*)buf, len, 0, (SOCKADDR*)(to_address.__raw), to_address.addrlen);
}
int udpSocket::RecvFrom(void* buf, size_t len, int flags, netAddress& from_address)
{
	recvfrom(_socket, (char*)buf, len, 0, (SOCKADDR*)(from_address.__raw), &from_address.addrlen);
}

}