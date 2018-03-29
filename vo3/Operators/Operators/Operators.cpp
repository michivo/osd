// Operators.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vector2d.h"
#include <iostream>
#include <string>

int main()
{
	Vector2d v{ -18, -12 };
	v = -v;
	std::cout << v << std::endl;
	v *= 2;
	std::cout << v << std::endl;
	v = v / 3;
	std::cout << v << std::endl;
	v = v + Vector2d{5, 5};
	std::cout << v << std::endl;
	const double norm = static_cast<double>(v); // casting to double gets the norm, see [1] in Vector2d.h
	v /= norm;
	std::cout << v << std::endl;
	v -= -v;
	std::cout << v << std::endl;
	v(); // calling function call operator normalizes the vector, see [2] in Vector2d.h
	std::cout << v << std::endl;
	v = Vector2d{ v[1], v[0] }; // array subscript operator, see [3] in Vector2d.h
	std::cout << v << std::endl;
	getchar();
    return 0;
}

