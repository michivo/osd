#pragma once

// interface for lamps
// it should be possible to turn a lamp on and off
// it should be possible to get the current state of the lamp

class ILamp {
public:
	virtual void turn_on() = 0;

	virtual void turn_off() = 0;

	virtual bool is_on() const = 0;

	// virtual destructor, as always!
	virtual ~ILamp() = 0;
};
