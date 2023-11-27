#ifndef MUTILS_IPADDRESS_H
#define MUTILS_IPADDRESS_H

#include <string>

namespace mutils
{

class netAddress
{
public:
	netAddress();
	netAddress(const char* address); //utf-8
	// 127.0.0.1:1605
	// [2001:db8::1]:3210

	std::string toString() const;

	alignas(16) unsigned char __raw[64];
	int addrlen;
	int version; //4 for ipv4, 6 for ipv6
};

}

#endif // !MUTILS_IPADDRESS_H
