#ifndef DEEPSOCKET_TEST_PFLOOD_H
#define DEEPSOCKET_TEST_PFLOOD_H

#include <vector>

#include "../include/types.h"

int PFlood_SendtoRegisterCallback(gatesendtocallback_t sendtocallback);
int PFlood_OnPacketArrive(DEEPSOCKET deepsock, void* packet, int packetlen);

DEEPSOCKCONTEXT PFlood_Open();
int PFlood_Close(DEEPSOCKCONTEXT deepsockcontext);

void PFlood_setFloodingGroup(const std::vector<DEEPSOCKET>& group);

#endif // !DEEPSOCKET_TEST_PFLOOD_H
