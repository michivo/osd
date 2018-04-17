#include "Pin.h"
#include "PiDigitalInput.h"
#include "PiDigitalOutput.h"

#include <wiringPi.h>

#include <iostream>
#include <chrono>
#include <atomic>

using namespace pi_io;

void button_was_pressed(Pin p, const std::chrono::system_clock::time_point& start_time,
	std::atomic_llong& ticks_since_press);

int main(void)
{
	std::chrono::system_clock::time_point start_time = std::chrono::high_resolution_clock::now();
	std::atomic_llong ticks_since_press{ 0 };

	const std::function<void(Pin)> button_handler = [&](Pin p) { return button_was_pressed(p, start_time, ticks_since_press); };;
	Pi_digital_output output{ Pin::bcm_2 };
	Pi_digital_input input{ Pin::bcm_22, Pull_up_down::off, Edge_type::rising, button_handler };

	for (int i = 0; i < 20; i++)
	{
		output.set_state(State::high);
		delay(500);
		output.set_state(State::low);
		delay(500);
		std::cout << (input.read() == State::high ? "HI" : "LO") << std::endl;
		if (ticks_since_press != 0)
			std::cout << "Ticks when button was pressed: " << ticks_since_press << std::endl;
	}
	return 0;
}


void button_was_pressed(Pin p, const std::chrono::system_clock::time_point& start_time,
	std::atomic_llong& ticks_since_press)
{
	const auto now = std::chrono::high_resolution_clock::now();
	auto delta_t_since_start = now - start_time;
	std::cout << "Button " << to_underlying(p) << " was pressed "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(delta_t_since_start).count()
		<< "ms after start.\n";
	ticks_since_press = delta_t_since_start.count();
}