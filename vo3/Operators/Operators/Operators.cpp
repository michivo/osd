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
	std::cout << v << std::endl; // (18, 12)

	v *= 2;
	std::cout << v << std::endl; // (36, 24)

	v = v / 3;
	std::cout << v << std::endl; // (12, 8)

	v = v + Vector2d{5, 5};
	std::cout << v << std::endl; // (17, 13)

	const double norm = static_cast<double>(v); // for demo/testing: casting to double gets the norm, see [1] in Vector2d.h
	v /= norm;

	std::cout << v << std::endl; // (0.794358, 0.60745)
	v -= -v;

	std::cout << v << std::endl; // (1.58872, 1.2149)

	v(); // for demo/testing: calling function call operator normalizes the vector, see [2] in Vector2d.h
	std::cout << v << std::endl; // (0.794358, 0.60745)

	v = Vector2d{ v[1], v[0] }; // array subscript operator, see [3] in Vector2d.h
	std::cout << v << std::endl; // (0.60745, 0.794358)

	const double dot_product = v * v;
	std::cout << "Dot product: " << dot_product << std::endl;
	getchar();
    return 0;
}

