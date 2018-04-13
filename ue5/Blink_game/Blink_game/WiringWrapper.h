#pragma once
#include "Pin.h"
#include "Enums.h"

class Pi_io_manager;

class Wiring_wrapper {
public:
	static Wiring_wrapper& instance()
	{
		static Wiring_wrapper instance_;
		return instance_;
	}

	State digital_read(Pin pin);

	void digital_write(Pin pin, State state);

	void set_callback(Pin pin, Edge_type edge_type, void(*callback)(void));

	void set_pin_mode(Pin pin, Mode mode);

private:
	Wiring_wrapper();

	constexpr static int map_pin(Pin pin);

	constexpr static int map_edge_type(Edge_type edge);

	constexpr static int map_mode(Mode mode);

	enum class Number_scheme { bcm, wiring_pi, physical };

	constexpr static Number_scheme scheme_ = Number_scheme::bcm;
};
