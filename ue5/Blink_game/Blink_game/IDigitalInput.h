#pragma once
#include "Enums.h"

namespace pi_io {

	class IDigital_input
	{
	public:
		virtual State read() = 0;

		virtual ~IDigital_input() = 0;
	};

}
