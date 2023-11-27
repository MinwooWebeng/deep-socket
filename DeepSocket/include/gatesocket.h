#ifndef DEEPSOCKET_GATESOCKET_H
#define DEEPSOCKET_GATESOCKET_H

#include <memory>
#include <map>
#include <tuple>
#include <string>

#include "types.h"

#include "protocol.h"
#include "session.h"

namespace ds
{

class GateSocket
{
public:
	GateSocket(unsigned short port, const char* domain, void* privatekey, int privatekeylen, const char* keyType);
	~GateSocket();

	int AddProtocol(
		const char* name,
		deepsockopencallback_t DeepsockOpenCallback,
		deepsockclosecallback_t DeepsockCloseCallback,
		deepsockonpacketarrcallback_t OnPacketArriveCallback,
		deepsockregistersendtocallback_t RegisterSendtoCallback);

	int Listen(int backlog);
	std::tuple<bool, std::shared_ptr<Session>> Accept(); //a copy of shared ptr exists in deepsockTable.
	int Connect(const char* address, const void* pubkey, int pubkeylen);

private:
	std::map<connectionid, std::shared_ptr<Session>> sessionTable;
	std::map<std::string, Protocol> protocolTable;
};

}

#endif // !DEEPSOCKET_GATESOCKET_H
