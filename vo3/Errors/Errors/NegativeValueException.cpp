#include "stdafx.h"
#include "NegativeValueException.h"
#include <string>


Negative_value_exception::Negative_value_exception(int value) : 
	error_message_(std::to_string(value) + " is not valid, only positive values are allowed!")
{
}

const char* Negative_value_exception::what() const
{
	return error_message_.c_str();
}
