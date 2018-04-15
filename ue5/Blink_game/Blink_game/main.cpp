#include "Pin.h"
#include "PiDigitalInput.h"
#include "PiDigitalOutput.h"

#include <wiringPi.h>

#include <iostream>

using namespace pi_io;

int main(void)
{
	Pi_digital_output output{ Pin::bcm_2 };
	Pi_digital_input input{ Pin::bcm_22, Pull_up_down::off, Edge_type::rising, [](Pin p) {std::cout << "Someone hit the button!\n"; } };

	for (int i = 0; i < 20; i++)
	{
		output.set_state(State::high);
		delay(500);
		output.set_state(State::low);
		delay(500);
		std::cout << (input.read() == State::high ? "HI" : "LO") << std::endl;
	}
	return 0;
}
