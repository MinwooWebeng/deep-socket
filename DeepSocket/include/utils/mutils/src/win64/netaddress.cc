#include "../../netaddress.h"

#include <string.h>
#include <iostream>

#include "../../utfconv.h"
#include "wsa_support.h"

namespace mutils
{

netAddress::netAddress() :
	version(4),
	addrlen(0)
{
	memset(__raw, sizeof(__raw), 0);
}
netAddress::netAddress(const char* address) :
	version(4),
	addrlen(static_cast<int>(sizeof(__raw)))
{
	auto addr_utf16 = utf8to16(address);

	int result = 0;

	memset(__raw, sizeof(__raw), 0);
	if ((result = WSAStringToAddress((LPWSTR)addr_utf16.c_str(), AF_INET, NULL, (SOCKADDR*)__raw, &addrlen))
		== 0)
	{
		//((SOCKADDR_IN*)__raw)->sin_port = htons(port);
		return;
	}

	//try ipv6
	addrlen = static_cast<int>(sizeof(__raw));
	memset(__raw, sizeof(__raw), 0);
	if ((result = WSAStringToAddress((LPWSTR)addr_utf16.c_str(), AF_INET6, NULL, (SOCKADDR*)__raw, &addrlen))
		== 0)
	{
		//((SOCKADDR_IN6*)__raw)->sin6_port = htons(port);
		version = 6;
		return;
	}

	memset(__raw, sizeof(__raw), 0); //error case, return invalidated address.
	addrlen = 0;
}
std::string netAddress::toString() const
{
	char16_t buf[128];
	unsigned int buflen = static_cast<int>(sizeof(__raw));
	if (WSAAddressToString((SOCKADDR*)__raw, addrlen, NULL, (LPWSTR)&buf, (LPDWORD)&buflen)
		!= 0)
	{
		return "";
	}

	auto addr_utf16 = std::u16string(buf, buflen);
	return utf16to8(addr_utf16);
}

}