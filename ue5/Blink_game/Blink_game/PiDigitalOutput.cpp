#include "PiDigitalOutput.h"
#include "WiringWrapper.h"

void Pi_digital_output::set_state(State state)
{
	Wiring_wrapper::instance().digital_write(pin_, state);
}

State Pi_digital_output::get_state()
{
	return Wiring_wrapper::instance().digital_read(pin_);
}

Pi_digital_output::Pi_digital_output(Pin pin) : pin_{ pin }
{
}
