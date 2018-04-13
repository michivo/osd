#pragma once
#include "IDigitalInput.h"

#include "Pin.h"
#include <functional>

class Wiring_wrapper;
class Pi_io_manager;

class Pi_digital_input : public IDigital_input
{
public:
	State read() override;

	void set_interrupt_handler(std::function<void()> handler);
	
	Pi_digital_input(Pi_digital_input&& other) = default;

private:
	Pi_digital_input(Pin pin);
	void on_interrupt();
	
	Pin pin_;
	std::function<void()> handler_;

	friend Pi_io_manager;
};

