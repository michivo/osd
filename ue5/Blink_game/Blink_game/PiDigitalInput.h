#pragma once
#include "IDigitalInput.h"

#include "Pin.h"
#include "PinHandle.h"

#include <functional>

namespace pi_io {

	class Pi_digital_input : public IDigital_input
	{
	public:
		Pi_digital_input(Pin pin, Pull_up_down pud = Pull_up_down::up, Edge_type edge = Edge_type::rising,
			std::function<void(Pin)> value_change_handler = nullptr);

		State read() override;

		Pi_digital_input(Pi_digital_input&& other) = default;

	private:
		Pin_handle pin_;
	};

}