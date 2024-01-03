#ifndef MUTILS_UDPSOCKET_H
#define MUTILS_UDPSOCKET_H

#include "netaddress.h"

namespace mutils
{

class udpSocket
{
public:
	udpSocket(const netAddress& local_address);
	~udpSocket();

	int SendTo(const void* buf, size_t len, const netAddress& to_address);
	int RecvFrom(void* buf, size_t len, int flags, netAddress& from_address);

private:
	uint64_t _socket; //native, HANDLE or file descripter.

};

}

#endif // !MUTILS_UDPSOCKET_H
