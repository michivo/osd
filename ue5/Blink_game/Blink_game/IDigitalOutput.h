#pragma once

#include "Enums.h"

class IDigital_output
{
public:
	virtual void set_state(State state) = 0;
	virtual State get_state() = 0;
	virtual ~IDigital_output() = 0;
};