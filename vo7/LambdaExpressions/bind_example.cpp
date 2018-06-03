#include "stdafx.h"
#include "bind_example.h"

#include <functional>
#include <iostream>
#include <random>
#include <map>
#include <string>

Holder::Holder(int value) : value_{ value }
{
}

int Holder::get_value() const
{
	return value_;
}

void Holder::set_value(int value)
{
	value_ = value;
}

std::map<int, int> get_distribution(int min, int max, int count)
{
	std::default_random_engine e;
	std::binomial_distribution<> distr(max - min, .5);
	const std::function<int()> rnd = std::bind(distr, e);

	std::map<int, int> hist;
	for (int n = 0; n < count; ++n)
		++hist[rnd() + min];

	return hist;
}

void bind_example()
{
	Holder h(3);
	h.set_value(4);

	const std::function<int()> getter = std::bind(&Holder::get_value, &h);
	std::cout << "Value is now " << getter() << '\n';

	const std::function<void()> setter = std::bind(&Holder::set_value, &h, 5);
	setter();
	std::cout << "Value is now " << getter() << '\n';

	using namespace std::placeholders; // required for placeholders like _1, _2, _3, ...
	const std::function<void(int)> param_setter = std::bind(&Holder::set_value, &h, _1);
	param_setter(42);
	std::cout << "Value is now " << getter() << '\n';

	const std::function<std::map<int, int>(int, int)> distribution = std::bind(&get_distribution, _1, _2, 100);
	auto hist = distribution(5, 15);
	for (const auto entry : hist)
		std::cout << entry.first <<	'\t' << std::string(entry.second, 'X') << '\n';
}
