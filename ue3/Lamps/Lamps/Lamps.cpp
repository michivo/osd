// Lamps.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DummyLamp.h"
#include "ILamp.h"

#include <iostream>

void print_state(const ILamp& lamp);

int main()
{
	// create a new dummy lamp, play around with it
	Dummy_lamp lamp;
	print_state(lamp);
	lamp.turn_on();
	print_state(lamp);
	lamp.turn_off();
	print_state(lamp);
	lamp.turn_off();
	print_state(lamp);
	lamp.turn_on();
	print_state(lamp);
	lamp.turn_on();
	print_state(lamp);

	getchar();
    return 0;
}

void print_state(const ILamp& lamp) {
	std::cout << "The lamp is " << (lamp.is_on() ? "ON" : "OFF") << std::endl;
}