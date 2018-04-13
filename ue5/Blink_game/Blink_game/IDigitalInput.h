#pragma once
#include "Enums.h"

class IDigital_input
{
public:
	virtual State read() = 0;

	virtual ~IDigital_input() = 0;
};
