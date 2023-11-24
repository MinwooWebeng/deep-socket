#include "line.h"

#include <iostream>
#include <vector>

#include "../include/deepsocket.h"
#include "p_echo.h"
#include "p_datagram.h"

std::tuple<bool, std::string> line()
{
	char A_publickey[1024];
	int A_publickey_len = 1024;
	char A_privkey[1024];
	int A_privkey_len = 1024;

	char B_publickey[1024];
	int B_publickey_len = 1024;
	char B_privkey[1024];
	int B_privkey_len = 1024;

	std::cout << "generating keys" << std::endl;
	//generate key pair for both node.
	//in practical use, keys will be loaded from local storage.
	if(gatesock_genkeypair("rsa4096", A_publickey, &A_publickey_len, A_privkey, &A_privkey_len) != 0)
	{
		return std::make_tuple(false, "failed to create gate key pair");
	}

	if (gatesock_genkeypair("rsa4096", B_publickey, &B_publickey_len, B_privkey, &B_privkey_len) != 0)
	{
		return std::make_tuple(false, "failed to create gate key pair");
	}

	std::cout << "open gate sockets" << std::endl;
	//open gate sockets
	GATESOCKET A_gsock = gatesocket(1600, "ipv4", A_privkey, A_privkey_len, "rsa4096");
	if (A_gsock == GATESOCKET_ERROR)
	{
		return std::make_tuple(false, "failed to create gate socket");
	}

	GATESOCKET B_gsock = gatesocket(1601, "ipv4", B_privkey, B_privkey_len, "rsa4096");
	if (B_gsock == GATESOCKET_ERROR)
	{
		return std::make_tuple(false, "failed to create gate socket");
	}

	std::cout << "add protocols" << std::endl;
	//add echo protocol for A peer, and datagram protocol for B peer.
	if (gatesockaddprotocol(
		A_gsock, "echo", 
		PEcho_OnPacketArrive, 
		PEcho_SendtoRegisterCallback,
		PEcho_Open,
		PEcho_Close) != 0)
	{
		return std::make_tuple(false, "failed to add echo protocol to gate socket");
	}

	if (gatesockaddprotocol(
		B_gsock, "datagram",
		PDatagram_OnPacketArrive,
		PDatagram_SendtoRegisterCallback,
		PDatagram_Open,
		PDatagram_Close) != 0)
	{
		return std::make_tuple(false, "failed to add datagram protocol to gate socket");
	}
	//actually, these are supported as default; there's no need to add.
	//just to demonstrate how to import third-party protocols.

	std::cout << "listen sockets" << std::endl;
	//both gate sockets start listening
	if (gatesocklisten(A_gsock, 5) != 0)
	{
		return std::make_tuple(false, "listen() failed on gate socket");
	}

	if (gatesocklisten(B_gsock, 5) != 0)
	{
		return std::make_tuple(false, "listen() failed on gate socket");
	}

	std::cout << "connecting" << std::endl;
	//node B connects to node A. this call immediately returns and handshake is asynchronous.
	if (gatesockconnect(B_gsock, "127.0.0.1/1601", A_publickey, A_publickey_len) != 0)
	{
		return std::make_tuple(false, "connect() returned error");
	}

	std::cout << "accepting" << std::endl;
	//both side needs to accept the connection.
	SESSIONHANDLE A_session = gatesockaccept(A_gsock);
	if (A_session == SESSIONHANDLE_ERROR) //gatesocket closed(or failed).
	{
		return std::make_tuple(false, "inbound accept() returned error");
	}

	SESSIONHANDLE B_session = gatesockaccept(B_gsock);
	if (B_session == SESSIONHANDLE_ERROR) //gatesocket closed(or failed).
	{
		return std::make_tuple(false, "outbound accept() returned error");
	}

	std::cout << "deep socket creating" << std::endl;
	//A creates echo channel on deep port 100.
	DEEPSOCKET A_dsock = deepsocket(A_session, 100, "echo");
	if (A_dsock == DEEPSOCKET_ERROR)
	{
		return std::make_tuple(false, "failed to open echo deep socket");
	}

	DEEPSOCKET B_dsock = deepsocket(B_session, 100, "datagram");
	if (B_dsock == DEEPSOCKET_ERROR)
	{
		return std::make_tuple(false, "failed to open echo deep socket");
	}

	std::cout << "datagram sending" << std::endl;
	//send datagram
	const char* message = "hello world";
	if (PDatagram_Sendto(getdscontext(B_dsock), message, strlen(message), 0) != strlen(message))
	{
		return std::make_tuple(false, "failed to send datagram");
	}
	
	std::cout << "datagram receiving" << std::endl;
	//receive echoed datagram
	char buf[32];
	if (PDatagram_Recvfrom(getdscontext(B_dsock), buf, 32) != strlen(message))
	{
		return std::make_tuple(false, "failed to receive datagram");
	}
	buf[strlen(message)] = 0;

	//compare return
	if (strncmp(message, buf, strlen(message)) != 0)
	{
		return std::make_tuple(false, "message corrupted");
	}

	std::cout << "closing deep socket" << std::endl;
	//close deep socket.
	if (deepsockclose(A_dsock) != 0)
	{
		return std::make_tuple(false, "failed to close deep socket");
	}

	if (deepsockclose(B_dsock) != 0)
	{
		return std::make_tuple(false, "failed to close deep socket");
	}

	std::cout << "disconnecting" << std::endl;
	//disconnect
	if (gatesockdisconnect(A_session) != 0)
	{
		return std::make_tuple(false, "failed to disconnect the inbound session");
	}

	if (gatesockdisconnect(B_session) != 0)
	{
		return std::make_tuple(false, "failed to disconnect the outbound session");
	}

	std::cout << "closing gate socket" << std::endl;
	//closing gate sockets
	if (gatesockclose(A_gsock) != 0)
	{
		return std::make_tuple(false, "failed to close gate socket");
	}

	if (gatesockclose(B_gsock) != 0)
	{
		return std::make_tuple(false, "failed to close gate socket");
	}

	return std::make_tuple(true, "success");
}