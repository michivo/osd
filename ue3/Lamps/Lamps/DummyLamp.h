#pragma once

#include "ILamp.h"

// dummy implementation of interface ILamp. It will just do some console output. 
// It is declared final, so you cannot derive from it.

class Dummy_lamp final : public ILamp {
public:
	// constructor, default initial state is off
	Dummy_lamp(bool initial_state = false);

	virtual void turn_on() override;

	virtual void turn_off() override;

	virtual bool is_on() const override;

private:
	bool is_on_;
};
