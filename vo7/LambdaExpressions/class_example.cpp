#include "stdafx.h"
#include "class_example.h"
#include <algorithm>
#include <iostream>

using namespace std;

Int_vector::Int_vector(std::vector<int> vector) : data_{vector}
{
}

void Int_vector::remove_if(std::function<bool(int)> criterion)
{
	data_.erase(std::remove_if(data_.begin(), data_.end(), criterion), data_.end());
}

void Int_vector::map_to(std::function<void(int&)> mapper)
{
	std::for_each(data_.begin(), data_.end(), mapper);
}

void Int_vector::print()
{
	const auto printer = [this](int i) { std::cout << "[" << i << "]:\t" << this->data_[i] << ", "; };

	int i = 0;
	std::for_each(data_.begin(), data_.end(), [this, &i](const int& val)
	{ // prints something like [2 of 3]: 5, so [index of size]: value
		std::cout << "[" << ++i << " of " << this->data_.size() << "]:\t" << val << "\n";
	});
	std::cout << "===================\n";
}

bool is_odd(int x)
{
	return x % 2 != 0;
}

void class_example()
{
	vector<int> vec(10);
	int i = 0;
	generate(begin(vec), end(vec), [&i]() -> int { return i++; }); // generates a list using a lambda
	Int_vector int_vec = vec;
	int_vec.print();
	int_vec.remove_if(is_odd); // functions can also be used for std::functions!
	int_vec.print();
	int_vec.map_to([](int &x) { x *= 2; });
	int_vec.print();
	int_vec.remove_if([](int x) { return x > 10; });
	int_vec.print();
}
