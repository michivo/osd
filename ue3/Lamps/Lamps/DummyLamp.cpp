#include "stdafx.h"
#include "DummyLamp.h"

#include <iostream>

Dummy_lamp::Dummy_lamp(bool initial_state /* = false */) : is_on_{ initial_state }
{
}

void Dummy_lamp::turn_on()
{
	if (is_on_) {
		return;
	}

	is_on_ = true;
	std::cout << "Lamp was turned ON!" << std::endl;
}

void Dummy_lamp::turn_off()
{
	if (!is_on_) {
		return;
	}

	is_on_ = false;
	std::cout << "Lamp was turned OFF!" << std::endl;
}

bool Dummy_lamp::is_on() const {
	return is_on_;
}