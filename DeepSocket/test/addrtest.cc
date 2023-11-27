#include "addrtest.h"

#include <iostream>

#include "../include/utils/mutils/netaddress.h"

std::tuple<bool, std::string> addrconv()
{
	const char* test_cases[] = {"127.0.0.1:1605", "0.0.0.0:1605", "255.255.255.255:2001", "1.2.3.4:7", "[2001:db8::1]:3210"};
	for (const char* c: test_cases)
	{
		auto ret = mutils::netAddress(c).toString();
		std::cout << ret << "\n";
		if (strcmp(ret.c_str(), c) != 0)
			return std::make_pair(false, std::string(ret.c_str()) +  std::string("|failed to convert address ") + std::string(c));
	}
	return std::make_pair(true, "success");
}
