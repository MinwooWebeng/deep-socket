#include "../include/deepsocket.h"

#include <string>
#include <new>

#include "../include/gatesocket.h"
#include "../include/utils/mutils/handle.h"

int gatesock_genkeypair(const char* type, void* pubkeydest, int* pubkeylen, void* privatekeydest, int* privatekeylen)
{
	const char* dummy = "dummy key";
	int dummy_len = static_cast<int>(strlen(dummy) + 1);
	memcpy(pubkeydest, dummy, dummy_len);
	*pubkeylen = dummy_len;
	memcpy(privatekeydest, dummy, dummy_len);
	*privatekeylen = dummy_len;
	return 0;
}

static inline GATESOCKET rtog(ds::GateSocket* r) { return { r }; }
static inline ds::GateSocket* gtor(GATESOCKET g) { return static_cast<ds::GateSocket*>(g._); }

static inline SESSIONHANDLE rtos(mutils::Handle<std::shared_ptr<ds::Session>>* r) { return { r }; }
static inline mutils::Handle<std::shared_ptr<ds::Session>>* stor(SESSIONHANDLE s)
{ 
	return static_cast<mutils::Handle<std::shared_ptr<ds::Session>>*>(s._);
}

GATESOCKET gatesocket(unsigned short port, const char* domain, void* privatekey, int privatekeylen, const char* keyType)
{
	return rtog(new (std::nothrow) ds::GateSocket(port, domain, privatekey, privatekeylen, keyType));
}
int gatesockaddprotocol(
	GATESOCKET gsock, const char* name,
	deepsockopencallback_t DeepsockOpenCallback,
	deepsockclosecallback_t DeepsockCloseCallback,
	deepsockonpacketarrcallback_t OnPacketArriveCallback,
	deepsockregistersendtocallback_t RegisterSendtoCallback
)
{
	return gtor(gsock)->AddProtocol(name, DeepsockOpenCallback, DeepsockCloseCallback, OnPacketArriveCallback, RegisterSendtoCallback);
}
int gatesocklisten(GATESOCKET gsock, int backlog)
{
	return gtor(gsock)->Listen(backlog);
}
SESSIONHANDLE gatesockaccept(GATESOCKET gsock)
{
	std::tuple<bool, std::shared_ptr<ds::Session>> result = gtor(gsock)->Accept();
	if (!std::get<0>(result))
		return SESSIONHANDLE_ERROR;

	auto handle = new(std::nothrow) mutils::Handle<std::shared_ptr<ds::Session>>(std::get<1>(result));
	return rtos(handle); //make it handle
}
int gatesockconnect(GATESOCKET gsock, const char* address, const void* pubkey, int pubkeylen)
{
	return gtor(gsock)->Connect(address, pubkey, pubkeylen);
}
int gatesockdisconnect(SESSIONHANDLE session)
{
	if (session == SESSIONHANDLE_ERROR)
		return 0;

	delete stor(session);
	return 0;
}
int gatesockclose(GATESOCKET gsock)
{
	if (gsock == GATESOCKET_ERROR)
		return 0;

	delete gtor(gsock);
	return 0;
}

DEEPSOCKET deepsocket(SESSIONHANDLE session, unsigned int dport, const char* protocol)
{
	return DEEPSOCKET_ERROR;
}
int deepsockclose(DEEPSOCKET dsock)
{
	return -1;
}

int sendtocontextclose(SENDTOCONTEXT scontext)
{
	return -1;
}
DEEPSOCKCONTEXT getdscontext(DEEPSOCKET dsock)
{
	return DEEPSOCKCONTEXT_ERROR;
}