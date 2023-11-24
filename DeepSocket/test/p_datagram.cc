#include "p_datagram.h"
#include "../include/deepsocket.h"

#include <algorithm>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

class PDatagram
{
public:
	PDatagram()
	:	sendto(NULLSENDTO),
		scontext(SENDTOCONTEXT_NULL)
	{}
	~PDatagram()
	{
		sendtocontextclose(scontext);
	}

	//current implementation is very inefficient
	int OnPacketArrive(void* packet, int packetlen)
	{
		auto lock = std::lock_guard<std::mutex>(datagram_mutex);
	
		datagram_buffer.push(std::string((const char*)packet, packetlen));
	
		datagram_cv.notify_one();
		return 0;
	}
	
	std::mutex datagram_mutex;
	std::condition_variable datagram_cv;
	std::queue<std::string> datagram_buffer;

	//user-level API
	int SendTo(const void* payload, int len, int option)
	{
		return sendto(scontext, payload, len, option);
	}
	int RecvFrom(void* buf, int buflen)
	{
		auto lock = std::unique_lock<std::mutex>(datagram_mutex);
		datagram_cv.wait(lock, [&]()
			{
				return datagram_buffer.empty();
			}
		);

		const std::string& front = datagram_buffer.front();
		int copylen = std::min(buflen, (int)front.length());
		memcpy(buf, &front[0], copylen);

		return copylen;
	}

	gatesendtocallback_t sendto;
	SENDTOCONTEXT scontext;
};

static inline DEEPSOCKCONTEXT rtoc(PDatagram* r) { return { r }; }
static inline PDatagram* ctor(DEEPSOCKCONTEXT s) { return static_cast<PDatagram*>(s._); }

DEEPSOCKCONTEXT PDatagram_Open()
{
	return rtoc(new PDatagram);
}
int PDatagram_Close(DEEPSOCKCONTEXT deepsockcontext)
{
	if (deepsockcontext == DEEPSOCKCONTEXT_ERROR)
		return -1;

	delete ctor(deepsockcontext);
	return 0;
}

int PDatagram_SendtoRegisterCallback(DEEPSOCKCONTEXT deepsock, gatesendtocallback_t sendtocallback, SENDTOCONTEXT context)
{
	ctor(deepsock)->sendto = sendtocallback;
	return 0;
}
int PDatagram_OnPacketArrive(DEEPSOCKCONTEXT deepsock, void* packet, int packetlen)
{
	return ctor(deepsock)->OnPacketArrive(packet, packetlen);
}

//user-level API
int PDatagram_Sendto(DEEPSOCKCONTEXT deepsock, const void* payload, int length, int option)
{
	return ctor(deepsock)->SendTo(payload, length, option);
}
int PDatagram_Recvfrom(DEEPSOCKCONTEXT deepsock, void* buf, int length)
{
	return ctor(deepsock)->RecvFrom(buf, length);
}