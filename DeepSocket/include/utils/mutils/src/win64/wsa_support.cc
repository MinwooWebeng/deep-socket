#include "wsa_support.h"

namespace mutils
{

wsaReq::wsaReq()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		throw "wsa startup failed";
	}
}
wsaReq::~wsaReq()
{
	WSACleanup();
}

wsaReq __wsa_data;

}