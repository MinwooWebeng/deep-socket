#ifndef DEEPSOCKET_TEST_PDATAGRAM_H
#define DEEPSOCKET_TEST_PDATAGRAM_H

#include "../include/types.h"

DEEPSOCKCONTEXT PDatagram_Open();
int PDatagram_Close(DEEPSOCKCONTEXT deepsockcontext);

int PDatagram_SendtoRegisterCallback(DEEPSOCKCONTEXT deepsock, gatesendtocallback_t sendtocallback, SENDTOCONTEXT context);
int PDatagram_OnPacketArrive(DEEPSOCKCONTEXT deepsock, void* packet, int packetlen);

int PDatagram_Sendto(DEEPSOCKCONTEXT deepsock, const void* payload, int length, int option);
int PDatagram_Recvfrom(DEEPSOCKCONTEXT deepsock, void* buf, int length); //blocking

#endif // !DEEPSOCKET_TEST_PDATAGRAM_H
