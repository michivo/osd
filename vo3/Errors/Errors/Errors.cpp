// Errors.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <cerrno>
#include <string>


int main()
{
	// c++ error handling
	std::vector<int> nums{ 2, 3, 4 };
	try {
		std::cout << nums.at(4) << std::endl;
	}
	catch(std::out_of_range ex) {
		std::cout << "This did not work out as planned: " << ex.what() << std::endl;
	}

	// c error handling
	errno = 0;
	double foo = std::sqrt(-3.4);
	if(errno != 0)
	{
		char err_message[1024];
		strerror_s(err_message, 1024, errno);
		std::cout << "Something went wrong: " << err_message << std::endl;
		errno = 0;
	}

	getchar();
    return 0;
}

