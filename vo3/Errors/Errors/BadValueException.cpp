#include "stdafx.h"
#include "BadValueException.h"
#include <string>


Bad_value_exception::Bad_value_exception(int value) :
	logic_error(std::to_string(value) + " is a bad value!")
{
}
