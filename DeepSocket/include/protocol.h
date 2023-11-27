#ifndef DEEPSOCKET_PROTOCOL_H
#define DEEPSOCKET_PROTOCOL_H

#include "types.h"

namespace ds
{

class Protocol
{
public:
	Protocol(
		deepsockopencallback_t _Open,
		deepsockclosecallback_t _Close,
		deepsockonpacketarrcallback_t _OnArrive,
		deepsockregistersendtocallback_t _RegSendto
	);
	
	const deepsockopencallback_t DeepsockOpen;
	const deepsockclosecallback_t DeepsockClose;
	const deepsockonpacketarrcallback_t OnPacketArrive;
	const deepsockregistersendtocallback_t RegisterSendto;
};

}

#endif // !DEEPSOCKET_PROTOCOL_H
