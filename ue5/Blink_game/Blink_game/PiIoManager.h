#pragma once
#include "Pin.h"
#include "Enums.h"

#include <memory>
#include <array>
#include <functional>
#include "PiDigitalOutput.h"
#include "PiDigitalInput.h"

class Pi_io_manager
{
public:
	static Pi_io_manager& instance()
	{
		static Pi_io_manager instance_;
		return instance_;
	}

	void add_input(Pin pin, Edge_type edge_tye = Edge_type::rising);
	void add_output(Pin pin);

	Pi_digital_input& get_input(Pin pin);
	Pi_digital_output& get_output(Pin pin);

	Pi_io_manager(Pi_io_manager &&other) = default;
	
private:
	Pi_io_manager();

	void assert_is_free(Pin pin);

	void handle_interrupt(Pin pin);

	static void forward_interrupt(Pin pin);

	static constexpr int io_count_ = 27;

	std::array<void(*)(), io_count_> interrupt_handlers_;

	std::array<std::unique_ptr<Pi_digital_input>, io_count_> inputs_;
	std::array<std::unique_ptr<Pi_digital_output>, io_count_> outputs_;
};

