// Errors.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NegativeValueException.h"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <cerrno>
#include <string>
#include "BadValueException.h"
#include "Dummy.h"

void do_stuff(int value);

void do_safe_stuff(int value) noexcept; // noexcept guarantees that this function will never throw!
                                        // if it still does, the exception cannot be caught and the
                                        // program will terminate


int main()
{
	// c++ error handling
	std::vector<int> nums{ 2, 3, 4 };
	try {
		std::cout << nums.at(4) << std::endl;
	}
	catch(const std::out_of_range& ex) {
		std::cout << "This did not work out as planned: " << ex.what() << std::endl;
	}

	// c error handling
	errno = 0;
	const double foo = std::sqrt(-3.4);
	if(std::isnan(foo) && errno != 0)
	{
		char err_message[1024];
		strerror_s(err_message, 1024, errno);
		std::cout << "Something went wrong: " << err_message << std::endl;
	}

	try 
	{
		Dummy d{ -1 };
	}
	catch(std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}

	try
	{
		Dummy d{ -1, false };
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}

	try
	{
		Dummy d{ -1, 10 };
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}

	try
	{
		do_stuff(-7);
	}
	catch(const Negative_value_exception& nex)
	{
		std::cout << nex.what();
	}
	// we do not handle Bad_value_exceptions here, they will crash our application

	getchar();
	try
	{
		do_safe_stuff(7);
	}
	catch(const std::exception &ex)
	{
		std::cout << "We will not reach this line. Ex will be thrown!" << std::endl;
	}

	getchar();
    return 0;
}

void do_stuff(int value)
{
	if (value < 0)
		throw Negative_value_exception{ value };

	if (value % 7 == 0)
		throw Bad_value_exception(value);

	std::cout << "I like " << value << std::endl;
}

void do_safe_stuff(int value) noexcept
{
	if (value % 7 == 0)
		throw Bad_value_exception(value); // this is nasty! we said noexcept, but throw...

	std::cout << "I like " << value << std::endl;
}