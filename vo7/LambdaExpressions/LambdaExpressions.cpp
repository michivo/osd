// LambdaExpressions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "numeric_example.h"
#include "simple_example.h"
#include "capture_example.h"
#include "class_example.h"

#include <iostream>
#include <string>
#include "bind_example.h"


int main()
{
	std::string separator( 80, '=' );
	std::cout << "Simple example:\n";
	simple_example();
	std::cout << separator << "\nNumeric example:\n";
	numeric_example();
	std::cout << separator << "\nCapture example:\n";
	capture_example();
	std::cout << separator << "\nClass example:\n";
	class_example();

	std::cout << separator << "\nBind example (no lambdas, but std::functions):\n";
	bind_example();
	getchar();
    return 0;
}

