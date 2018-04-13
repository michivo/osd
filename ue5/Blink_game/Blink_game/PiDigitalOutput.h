#pragma once
#include "IDigitalOutput.h"

#include "Pin.h"
#include "PinHandle.h"

class Pi_io_manager;
class Wiring_wrapper;

class Pi_digital_output : public IDigital_output
{
public:
	Pi_digital_output(Pin pin);

	void set_state(State state) override;
	State get_state() override;

	Pi_digital_output(Pi_digital_output&& other) = default;

private:
	Pin_handle pin_;
};
