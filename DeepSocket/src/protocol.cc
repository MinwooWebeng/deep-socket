#include "../include/protocol.h"

namespace ds
{

Protocol::Protocol(
	deepsockopencallback_t _Open,
	deepsockclosecallback_t _Close,
	deepsockonpacketarrcallback_t _OnArrive,
	deepsockregistersendtocallback_t _RegSendto
)	:
	DeepsockOpen(_Open),
	DeepsockClose(_Close),
	OnPacketArrive(_OnArrive),
	RegisterSendto(_RegSendto)
{}

}
