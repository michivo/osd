#pragma once
#include <stdexcept>

// class name should end with "exception"
// custom exception classes should always be derived from one std::exception or or
// one of the classes derived from it
class Negative_value_exception : std::exception
{
public:
	Negative_value_exception(int actual_value);
	const char* what() const override;
	
private:
	std::string error_message_;
};


