#ifndef MUTILS_SRC_WSASUPPORT_H
#define MUTILS_SRC_WSASUPPORT_H

#include <WinSock2.h>
#pragma comment (lib, "Ws2_32.lib")

#include <WS2tcpip.h>

namespace mutils
{

class wsaReq
{
public:
	wsaReq();
	~wsaReq();

private:
	WSADATA wsaData;
};

extern wsaReq __wsa_data;

}

#endif // !MUTILS_SRC_WSASUPPORT_H
