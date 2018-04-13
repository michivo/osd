#include "PiIoManager.h"

#include <wiringPi.h>

#include <iostream>

int main(void)
{
	Pi_io_manager::instance().add_input(Pin::bcm_2);
	Pi_io_manager::instance().add_output(Pin::bcm_3);

	auto& input = Pi_io_manager::instance().get_input(Pin::bcm_2);
	input.set_interrupt_handler([]() {std::cout << "Someone hit the button!\n"; });
	auto& output = Pi_io_manager::instance().get_output(Pin::bcm_3);
	for(int i =0; i < 100; i++)
	{
		output.set_state(input.read());
		delay(500);
	}
	return 0;
}
