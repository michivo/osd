#pragma once
#include <vector>

class Dummy
{
public:
	Dummy(int size);
	Dummy(int size, bool dummy);
	Dummy(int size, int dummy);
	virtual ~Dummy(); // destructor is always implicitly noexcept. causing an exception in a 
	                  // destructor is bad and will terminate your application

private:
	std::vector<int> values_;
};

