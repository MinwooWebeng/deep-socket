#ifndef DEEPSOCKET_TYPES_H
#define DEEPSOCKET_TYPES_H

#include <stdint.h>

//this header file should not be copied to the published lib/dll header.

#define TYPEDEF_HANDLE(__NAME__) struct __NAME__ { void* _; bool operator<(const __NAME__& rhs) const { return _ < rhs._; } bool operator==(const __NAME__& rhs) const{ return _ == rhs._; } };

//struct { void* _; } is just to help type checker.
TYPEDEF_HANDLE(GATESOCKET) //reference of the UDP socket wrapper
TYPEDEF_HANDLE(SESSIONHANDLE) //reference of a session from initial handshake. connection migration does not alter this.
TYPEDEF_HANDLE(DEEPSOCKET) //reference of the deep socket.

typedef bool (*gateacceptcallback_t)(SESSIONHANDLE session);

TYPEDEF_HANDLE(DEEPSOCKCONTEXT) //internals depend on protocol implementations
typedef DEEPSOCKCONTEXT(*deepsockopencallback_t)();
typedef int (*deepsockclosecallback_t)(DEEPSOCKCONTEXT deepsockcontext);

TYPEDEF_HANDLE(SENDTOCONTEXT)
typedef int (*gatesendtocallback_t)(SENDTOCONTEXT context, const void* packet, int packetlen, int option); //creates a frame. without option, this may not immediatly generate a packet. 
typedef int (*deepsockregistersendtocallback_t)(DEEPSOCKCONTEXT deepsock, gatesendtocallback_t sendtocallback, SENDTOCONTEXT context);
typedef int (*deepsockonpacketarrcallback_t)(DEEPSOCKCONTEXT deepsock, void* packet, int packetlen);

//**important!! these values are absolute
//internal implementation uses new(std::nothrow)
constexpr GATESOCKET GATESOCKET_ERROR = { nullptr };
constexpr SESSIONHANDLE SESSIONHANDLE_ERROR = { nullptr };
constexpr DEEPSOCKET DEEPSOCKET_ERROR = { nullptr };
constexpr DEEPSOCKCONTEXT DEEPSOCKCONTEXT_ERROR = { nullptr };
constexpr SENDTOCONTEXT SENDTOCONTEXT_NULL = { nullptr };

int NULLSENDTO(SENDTOCONTEXT, const void*, int, int);

//constexpr unsigned int SESSION_UNKNOWN_ERROR = -1; //error code higher than 5 is all considered unknown error. (reserved for the future)

/////////////////////// low-level protocol related

typedef uint32_t connectionid;

#endif // !DEEPSOCKET_TYPES_H
