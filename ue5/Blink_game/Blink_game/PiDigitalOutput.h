#pragma once
#include "IDigitalOutput.h"

#include "Pin.h"

class Pi_io_manager;
class Wiring_wrapper;

class Pi_digital_output : public IDigital_output
{
public:
	void set_state(State state) override;
	State get_state() override;

	Pi_digital_output(Pi_digital_output&& other) = default;

private:
	Pi_digital_output(Pin pin);

	Pin pin_;

	friend Pi_io_manager;
};
