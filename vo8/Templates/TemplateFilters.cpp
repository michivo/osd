#include "stdafx.h"
#include <vector>
#include <functional>
#include <iostream>

template<typename T>
std::vector<T> filter(const std::vector<T>& source, std::function<bool(T)> filter_func)
{
	std::vector<T> result;
	for (auto val : source)
	{
		if (filter_func(val))
		{
			result.push_back(val);
		}
	}

	return result;
}

template<typename T>
void print(const std::vector<T>& values)
{
	for (auto val : values)
	{
		std::cout << val << " - ";
	}
	std::cout << std::endl;
}

template<typename T, T Limit>
bool filter_smaller(T val)
{
	return val < Limit;
}


void filter_demo()
{
	std::vector<int> ints = { 9, 8, 6, 5, 1, 2, 5, 4 };
	std::vector<double> doubles = { 1.23, 10.3, 10.45, 23.5, 12.3, 33.3, 100.9, 1.2 };

	auto odd_ints = filter<int>(ints, [](int x) {return x % 2 == 1; });
	print(odd_ints);

	auto larger_filter = [](auto x, auto y) { return x > y; };
	auto large_ints = filter<int>(ints, [=](int x) {return larger_filter(x, 5); });
	auto large_doubles = filter<double>(doubles, [=](double x) {return larger_filter(x, 10.4); });

	auto small_ints = filter<int>(ints, filter_smaller<int, 5>);

	// MFA: the following line does not work. only integral and enumeration types are supported here!
	// auto small_doubles = filter<double>(doubles, filter_smaller<double, 5.0>); 

	print(odd_ints);
	print(large_ints);
	print(large_doubles);
	print(small_ints);
}