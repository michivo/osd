#include "stdafx.h"
#include "capture_example.h"
#include <iostream>


void capture_example()
{
	auto x = 7;
	const auto x_plus = [x](int z) { return x + z; }; // x is "captured" by the lambda expression. 
	                                          // it is a variable declared outside of the lambda
	                                          // that can be used in the lambda's body. it is captured by value!
	
	auto y = x_plus(5); // adds x to 5, so y will be 12

	const auto add_to_x = [&x](int z) { x += z; }; // x is now captured by reference - so calling this 
	                                                       // lambda will alter x's value
	
	add_to_x(16); // x will have value 23

	const auto add = [=]() { return x + y; }; // [=] captures all variables from surrounding scope by value
	auto a = add();

	const auto swap = [&]() // [&] captures all variables by reference
	{
		x += y; 
		y = x - y; 
		x -= y;
	};

	swap(); // swaps x and y, so x will be 12, y will be 23 and a will be 35

	std::cout << "x: " << x << ", y: " << y << ", a: " << a << "\n";
}
