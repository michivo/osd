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
#include "ClassHierarchy.h"

void do_stuff(int value);

void do_safe_stuff(int value) noexcept; // noexcept guarantees that this function will never throw!
                                        // if it still does, the exception cannot be caught and the
                                        // program will terminate


void do_dummy_tests()
{
	try 
	{
		Dummy d{ -1 }; // default ctor - will throw immediately
	}
	catch(std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}

	try
	{
		Dummy d{ -1, false }; // ctor with dummy bool value - will catch and rethrow in function try block
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}

	try
	{
		Dummy d{ -1, 10 }; // ctor with dummy int value - will catch and rethrow in normal try/catch block
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void noexcept_test()
{
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
}

void combined_class_test()
{
	std::vector<int> numbers{ 3, 5, 7, 15, 21, 36, 11, 33, 55, 66, 165, 231, 393, 13, 2 };
	for (auto x : numbers)
	{
		std::cout << "Testing with " << x << std::endl;
		try {
			Combined c{ x };
		}
		catch(std::logic_error& err)
		{
			std::cout << "Ex was thrown: " << err.what() << std::endl;
		}
		std::cout << "-----------------------------------------------------" << std::endl;
	}
}

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

	do_dummy_tests();
	combined_class_test();
	noexcept_test();

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