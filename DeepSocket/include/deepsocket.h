#ifndef DEEPSOCKET_H
#define DEEPSOCKET_H

#include "types.h"

int gatesock_genkeypair(const char* type, void* pubkeydest, int* pubkeylen, void* privatekeydest, int* privatekeylen);

GATESOCKET gatesocket(unsigned short port, const char* domain, void* privatekey, int privatekeylen, const char* keyType); //only AF_INET or AF_INET6 or both(duel socket)
int gatesockaddprotocol(
	GATESOCKET gsock, const char* name,
	deepsockopencallback_t DeepsockOpenCallback,
	deepsockclosecallback_t DeepsockCloseCallback,
	deepsockonpacketarrcallback_t OnPacketArriveCallback, 
	deepsockregistersendtocallback_t RegisterSendtoCallback
); //name must be shorter than 64 bytes, including null.
int gatesocklisten(GATESOCKET gsock, int backlog);
SESSIONHANDLE gatesockaccept(GATESOCKET gsock); //this substitutes accept().
int gatesockconnect(GATESOCKET gsock, const char* address, const void* pubkey, int pubkeylen); //this immediately returns.
int gatesockdisconnect(SESSIONHANDLE session);
int gatesockclose(GATESOCKET gsock); //duplicate close is undefined behavior

//deep sockets are opened under session.
DEEPSOCKET deepsocket(SESSIONHANDLE session, unsigned int dport, const char* protocol);
int deepsockclose(DEEPSOCKET dsock);

/*
if gatesocket closes while accept() is called and blocked, it is unblocked returning SESSIONHANDLE_ERROR.
this automatically kills all connections, but does not cleanup each session.
all sessions are still valid after gate socket close; just cannot send/receive packets.
Also, closing the session does not invalidate each deep socket; just cannot communicate/create new deep sockets.
if deepsocket closes, it calles OnProtocolArrive() with packet length -1 (0 is a valid packet!).
*/

///// for deep socket protocol implementation
int sendtocontextclose(SENDTOCONTEXT scontext);
DEEPSOCKCONTEXT getdscontext(DEEPSOCKET dsock);

#endif // !DEEPSOCKET_H
