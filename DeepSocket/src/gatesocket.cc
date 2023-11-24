#include "../include/gatesocket.h"

namespace ds
{

GateSocket::GateSocket(unsigned short port, const char* domain, void* privatekey, int privatekeylen, const char* keyType)
{

}
GateSocket::~GateSocket()
{

}

int GateSocket::AddProtocol(
	const char* name,
	deepsockonpacketarrcallback_t OnPacketArriveCallback,
	deepsockregistersendtocallback_t RegisterSendtoCallback,
	deepsockopencallback_t DeepsockOpenCallback,
	deepsockclosecallback_t DeepsockCloseCallback)
{
	return -1;
}

int GateSocket::Listen(int backlog)
{
	return -1;
}
std::tuple<bool, std::shared_ptr<Session>> GateSocket::Accept()
{
	return std::make_tuple(false, nullptr);
}
int GateSocket::Connect(const char* address, const void* pubkey, int pubkeylen)
{
	return -1;
}

}
