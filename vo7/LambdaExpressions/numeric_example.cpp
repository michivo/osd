#include "stdafx.h"

#include <iostream>
#include <vector>
#include <functional>
#include <climits>

int aggregate(std::vector<int> numbers, std::function<int(int, int)> aggregator, int seed = 0)
{
	int result = seed;
	for (auto x : numbers)
	{
		result = aggregator(x, result);
	}
	return result;
}

void numeric_example()
{
	const std::vector<int> numbers{ 2, 1, 3, 4, 2 };
	const auto sum = aggregate(numbers, [](int x, int y) {return x + y; });
	const auto product = aggregate(numbers, [](int x, int y) {return x * y; }, 1);
	const auto max = aggregate(numbers, [](int x, int y) {return x > y ? x : y; }, INT_MIN);
	const auto min = aggregate(numbers, [](int x, int y) {return x > y ? y : x; }, INT_MAX);
	std::cout << "Sum:\t" << sum
		<< "\nProd:\t" << product
		<< "\nMax:\t" << max
		<< "\nMin:\t" << min << "\n";
}