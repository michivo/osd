#include "stdafx.h"
#include "CountingThing.h"
#include <iostream>

int counting_thing::current_instances_ = 0;
int counting_thing::total_instances_ = 0;

counting_thing::counting_thing() : instance_number_{ total_instances_++ }
{
	++current_instances_;

	static int local_counter = current_instances();
	std::cout << "Local instance count: " << local_counter << std::endl;
}

counting_thing::counting_thing(const counting_thing& other) : instance_number_{ other.instance_number_ }
{
	++total_instances_;
	++current_instances_;
}

counting_thing::counting_thing(counting_thing&& other) noexcept : instance_number_{ other.instance_number_ }
{
	other.instance_number_ = 0;
	++total_instances_;
	++current_instances_;
}

counting_thing& counting_thing::operator=(const counting_thing& rhs)
{
	if (this == &rhs)
		return *this;

	instance_number_ = rhs.instance_number_;
	return *this;
}

counting_thing& counting_thing::operator=(counting_thing&& rhs) noexcept
{
	if (this == &rhs)
		return *this;

	instance_number_ = rhs.instance_number_;
	rhs.instance_number_ = 0;
	return *this;
}

counting_thing::~counting_thing()
{
	--current_instances_;
}

int counting_thing::total_instances()
{
	return total_instances_;
}

int counting_thing::current_instances()
{
	return current_instances_;
}

int counting_thing::instance_number() const
{
	return instance_number_;
}
