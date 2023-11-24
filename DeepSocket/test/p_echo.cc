#include "p_echo.h"
#include "../include/deepsocket.h"

class PEcho
{
public:
	PEcho()
	:	sendto(NULLSENDTO),
		scontext(SENDTOCONTEXT_NULL)
	{}
	~PEcho()
	{
		sendtocontextclose(scontext);
	}

	gatesendtocallback_t sendto;
	SENDTOCONTEXT scontext;
};

static inline DEEPSOCKCONTEXT rtoc(PEcho* r) { return { r }; }
static inline PEcho* ctor(DEEPSOCKCONTEXT s) { return static_cast<PEcho*>(s._); }

DEEPSOCKCONTEXT PEcho_Open()
{
	return rtoc(new PEcho);
}
int PEcho_Close(DEEPSOCKCONTEXT deepsockcontext)
{
	if (deepsockcontext == DEEPSOCKCONTEXT_ERROR)
		return -1;

	delete ctor(deepsockcontext);
	return 0;
}

int PEcho_SendtoRegisterCallback(DEEPSOCKCONTEXT deepsock, gatesendtocallback_t sendtocallback, SENDTOCONTEXT context)
{
	ctor(deepsock)->sendto = sendtocallback;
	return 0;
}
int PEcho_OnPacketArrive(DEEPSOCKCONTEXT deepsock, void* packet, int packetlen)
{
	auto pecho = ctor(deepsock);
	return pecho->sendto(pecho->scontext, packet, packetlen, 0);
}
