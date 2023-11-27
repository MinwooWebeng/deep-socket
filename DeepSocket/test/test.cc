#include <iostream>

#include "line.h"
#include "addrtest.h"

int main() {
	//auto result = line();

	auto result = addrconv();
	if (std::get<0>(result)) 
	{
		std::cout << "SUCCESS" << std::endl;
	}
	else
	{
		std::cout << "[FAIL] " << std::get<1>(result) << std::endl;
	}
}