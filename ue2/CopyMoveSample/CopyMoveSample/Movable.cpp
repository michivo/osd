#include "stdafx.h"
#include "Movable.h"

#include <iostream>

int Movable::instance_count_ = 0;
int Movable::array_size_ = 5;

Movable::Movable() : instance_number_{ ++instance_count_ }, dummy_ptr_{ new int[array_size_] {1,2,3,4,5} }
{
	std::cout << "Movable #" << instance_number_ << ": Default constructor" << std::endl;
}

Movable::Movable(const Movable & other) : instance_number_{ ++instance_count_ }
{	// allocate array
	dummy_ptr_ = new int[array_size_];
	std::copy(other.dummy_ptr_, other.dummy_ptr_ + array_size_, dummy_ptr_);

	std::cout << "Movable #" << instance_number_ << ": Copy constructor, copying #" << other.instance_number_ << std::endl;
	// we do NOT want to copy the instance number, so we can better track which instances we are dealing with
}

Movable::Movable(Movable && other) : instance_number_{ ++instance_count_ }, dummy_ptr_{ other.dummy_ptr_ } // set dummy_ptr_ to other's dummy_ptr_
{
	other.dummy_ptr_ = nullptr; // set other's dummy_ptr_ to nullptr, so other cannot do anything with it
	std::cout << "Movable #" << instance_number_ << ": Move constructor, moving #" << other.instance_number_ << std::endl;
}


Movable::~Movable()
{
	// free memory
	delete[] dummy_ptr_;
	std::cout << "Movable #" << instance_number_ << ": Destructor" << std::endl;
}

Movable & Movable::operator=(const Movable & other)
{	
	if (&other != this) { // skip copying for self-assignment
	    // copy data
		std::copy(other.dummy_ptr_, other.dummy_ptr_ + array_size_, dummy_ptr_);
	}

	// we do NOT want to copy the instance number, so we can better track which instances we are dealing with
	std::cout << "Movable #" << instance_number_ << ": Assignment operator, assigning #" << other.instance_number_ << std::endl;
	return *this;
}

Movable & Movable::operator=(Movable && other)
{
	if (this != &other) // avoid self assignment, which should not happen anyway
	{
		delete[] dummy_ptr_; // first delete our own dummy_ptr_, we won't need it
		dummy_ptr_ = other.dummy_ptr_; // take over other's dummy_ptr_
		other.dummy_ptr_ = nullptr; // set other's dummy_ptr_ to nullptr, so other can't do anything with it
	}

	std::cout << "Movable #" << instance_number_ << ": Move Assignment operator, assigning #" << other.instance_number_ << std::endl;
	return *this;
}


Movable create_movable() {
	std::cout << "--- Start create_movable" << std::endl;
	Movable c; // call to default constructor
	std::cout << "--- End create_movable" << std::endl;
	return c; // move constructor to temporary
}

Movable play_with_movable(Movable c) {
	std::cout << "--- Start play_with_movable" << std::endl;
	Movable a{ c }; // copy constructor
	std::cout << "--- Mid play_with_movable" << std::endl;
	a = c; // copy assignment operator
	std::cout << "--- End play_with_movable" << std::endl;
	return a; // move constructor to temporary
}

void test_movable() {
	std::cout << "--- Start Test Movable" << std::endl;
	Movable a; // default constructor
	std::cout << "--- Call create_movable" << std::endl;
	a = create_movable(); // move assignment operator, assigning return value of create_movable to a
	std::cout << "--- Returned from create_movable, call play_with_movable" << std::endl;
	a = play_with_movable(a); // move assignment operator, assigning return value of create_movable to a
	std::cout << "--- Returned from play_with_movable" << std::endl;
	Movable c = std::move(a); // move constructor
	a = std::move(c); // move assignemnt operator
}