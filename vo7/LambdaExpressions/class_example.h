#pragma once
#include <vector>
#include <functional>

class Int_vector
{
public:
	Int_vector(std::vector<int> vector);

	// removes all elements from the vector that do not fulfill the given criterion
	void remove_if(std::function<bool(int)> criterion);

	// maps all values in the vector to different values (e.g. if you want to add 2 to all elements)
	void map_to(std::function<void(int&)> mapper);

	void print();

private:
	std::vector<int> data_;
};

void class_example();
