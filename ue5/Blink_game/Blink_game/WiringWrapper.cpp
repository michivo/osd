#include "WiringWrapper.h"
#include "Pin.h"

#include <wiringPi.h>

#include <sstream>

State Wiring_wrapper::digital_read(Pin pin)
{
	return State(digitalRead(map_pin(pin)));
}

void Wiring_wrapper::digital_write(Pin pin, State state)
{
	digitalWrite(map_pin(pin), static_cast<int>(state));
}

void Wiring_wrapper::set_callback(Pin pin, Edge_type edge_type, void(*callback)(void))
{
	wiringPiISR(map_pin(pin), map_edge_type(edge_type), callback);
}

void Wiring_wrapper::set_pin_mode(Pin pin, Mode mode)
{
	pinMode(map_pin(pin), map_mode(mode));
}

Wiring_wrapper::Wiring_wrapper()
{
	int result = 0;
	switch (scheme_)
	{
	case Number_scheme::wiring_pi:
		result = wiringPiSetup();
		break;
	case Number_scheme::physical:
		result = wiringPiSetupPhys();
		break;
	default:
		result = wiringPiSetupGpio();
	}

	if (result < 0) {
		std::ostringstream err_message;
		err_message << "Error setting up wiring pi, failed with error code " << result;
		throw std::runtime_error(err_message.str());
	}
}

constexpr int Wiring_wrapper::map_pin(Pin pin)
{
	return scheme_ == Number_scheme::wiring_pi ? wiring_pi_number(pin) :
		scheme_ == Number_scheme::physical ? physical_number(pin) :
		bcm_number(pin);
}

constexpr int Wiring_wrapper::map_edge_type(Edge_type edge)
{
	return edge == Edge_type::rising ? INT_EDGE_RISING :
		edge == Edge_type::falling ? INT_EDGE_FALLING :
		edge == Edge_type::both ? INT_EDGE_BOTH :
		INT_EDGE_SETUP;
}

constexpr int Wiring_wrapper::map_mode(Mode mode)
{
	return mode == Mode::in ? INPUT :
		mode == Mode::out ? OUTPUT :
		PWM_OUTPUT;
}
