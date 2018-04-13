#include "PiDigitalInput.h"
#include "WiringWrapper.h"

State Pi_digital_input::read()
{
	auto val = Wiring_wrapper::instance().digital_read(pin_);
	return State(val);
}

void Pi_digital_input::set_interrupt_handler(std::function<void()> handler)
{
	handler_ = handler;
}

Pi_digital_input::Pi_digital_input(Pin pin) : pin_{ pin }, handler_(nullptr)
{
}

void Pi_digital_input::on_interrupt()
{
	if(handler_)
		handler_();
}
