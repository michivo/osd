#pragma once
#include <stdexcept>

class Bad_value_exception : std::logic_error
{
public:
	Bad_value_exception(int value);
};

