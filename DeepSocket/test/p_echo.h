#ifndef DEEPSOCKET_TEST_PECHO_H
#define DEEPSOCKET_TEST_PECHO_H

#include "../include/types.h"

DEEPSOCKCONTEXT PEcho_Open();
int PEcho_Close(DEEPSOCKCONTEXT deepsockcontext);

int PEcho_SendtoRegisterCallback(DEEPSOCKCONTEXT deepsock, gatesendtocallback_t sendtocallback, SENDTOCONTEXT context);
int PEcho_OnPacketArrive(DEEPSOCKCONTEXT deepsock, void* packet, int packetlen);


#endif // !DEEPSOCKET_TEST_PECHO_H
