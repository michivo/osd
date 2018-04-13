#include "PiIoManager.h"

#include "WiringWrapper.h"

#include <memory>
#include <sstream>
#include <functional>

Pi_io_manager::Pi_io_manager()
{
	interrupt_handlers_[0] = []() { forward_interrupt(Pin::bcm_0); };
	interrupt_handlers_[1] = []() { forward_interrupt(Pin::bcm_1); };
	interrupt_handlers_[2] = []() { forward_interrupt(Pin::bcm_2); };
	interrupt_handlers_[3] = []() { forward_interrupt(Pin::bcm_3); };
	interrupt_handlers_[4] = []() { forward_interrupt(Pin::bcm_4); };
	interrupt_handlers_[5] = []() { forward_interrupt(Pin::bcm_5); };
	interrupt_handlers_[6] = []() { forward_interrupt(Pin::bcm_6); };
	interrupt_handlers_[7] = []() { forward_interrupt(Pin::bcm_7); };
	interrupt_handlers_[8] = []() { forward_interrupt(Pin::bcm_8); };
	interrupt_handlers_[9] = []() { forward_interrupt(Pin::bcm_9); };
	interrupt_handlers_[10] = []() { forward_interrupt(Pin::bcm_10); };
	interrupt_handlers_[11] = []() { forward_interrupt(Pin::bcm_11); };
	interrupt_handlers_[12] = []() { forward_interrupt(Pin::bcm_12); };
	interrupt_handlers_[13] = []() { forward_interrupt(Pin::bcm_13); };
	interrupt_handlers_[14] = []() { forward_interrupt(Pin::bcm_14); };
	interrupt_handlers_[15] = []() { forward_interrupt(Pin::bcm_15); };
	interrupt_handlers_[16] = []() { forward_interrupt(Pin::bcm_16); };
	interrupt_handlers_[17] = []() { forward_interrupt(Pin::bcm_17); };
	interrupt_handlers_[18] = []() { forward_interrupt(Pin::bcm_18); };
	interrupt_handlers_[19] = []() { forward_interrupt(Pin::bcm_19); };
	interrupt_handlers_[20] = []() { forward_interrupt(Pin::bcm_20); };
	interrupt_handlers_[21] = []() { forward_interrupt(Pin::bcm_21); };
	interrupt_handlers_[22] = []() { forward_interrupt(Pin::bcm_22); };
	interrupt_handlers_[23] = []() { forward_interrupt(Pin::bcm_23); };
	interrupt_handlers_[24] = []() { forward_interrupt(Pin::bcm_24); };
	interrupt_handlers_[25] = []() { forward_interrupt(Pin::bcm_25); };
	interrupt_handlers_[26] = []() { forward_interrupt(Pin::bcm_26); };
}

void Pi_io_manager::add_input(Pin pin, Edge_type edge_tye)
{
	assert_is_free(pin);

	Wiring_wrapper::instance().set_pin_mode(pin, Mode::in);
	const auto pin_number = static_cast<int>(pin);
	inputs_[pin_number] = std::make_unique<Pi_digital_input>(Pi_digital_input{ pin });
	Wiring_wrapper::instance().set_callback(pin, edge_tye, interrupt_handlers_[pin_number]);
}

void Pi_io_manager::add_output(Pin pin)
{
	assert_is_free(pin);

	Wiring_wrapper::instance().set_pin_mode(pin, Mode::out);
	outputs_[static_cast<int>(pin)] = std::make_unique<Pi_digital_output>(Pi_digital_output{ pin });
}

Pi_digital_input& Pi_io_manager::get_input(Pin pin)
{
	const auto pin_number = static_cast<int>(pin);
	if (!inputs_[pin_number])
	{
		std::ostringstream err_message;
		err_message << "Pin " << pin_number << " is not configured as input!";
		throw std::logic_error(err_message.str());
	}

	return *inputs_[pin_number];
}

Pi_digital_output& Pi_io_manager::get_output(Pin pin)
{
	const auto pin_number = static_cast<int>(pin);
	if (!outputs_[pin_number])
	{
		std::ostringstream err_message;
		err_message << "Pin " << pin_number << " is not configured as output!";
		throw std::logic_error(err_message.str());
	}

	return *outputs_[pin_number];
}

void Pi_io_manager::assert_is_free(Pin pin)
{
	const auto pin_number = static_cast<int>(pin);
	if (inputs_[pin_number] || outputs_[pin_number])
	{
		std::ostringstream err_message;
		err_message << "Pin " << pin_number << " is already in use!";
		throw std::logic_error(err_message.str());
	}
}

void Pi_io_manager::handle_interrupt(Pin pin)
{
	const auto pin_number = static_cast<int>(pin);
	if (!inputs_[pin_number])
	{
		std::ostringstream err_message;
		err_message << "Pin " << pin_number << " is not configured as input!";
		throw std::logic_error(err_message.str());
	}

	inputs_[pin_number]->on_interrupt();
}


void Pi_io_manager::forward_interrupt(Pin pin)
{
	instance().handle_interrupt(pin);
}
