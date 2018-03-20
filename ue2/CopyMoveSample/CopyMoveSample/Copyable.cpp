#include "stdafx.h"
#include "Copyable.h"

#include <iostream>
#include <iterator>
#include <memory>

int Copyable::instance_count_ = 0;
int Copyable::array_size_ = 5;

// Default constructor
Copyable::Copyable() : 
	instance_number_{ ++instance_count_ }, dummy_ptr_{ new int[array_size_] {1,2,3,4,5} }
{
	std::cout << "Copyable #" << instance_number_ << ": Default constructor" << std::endl;
}

// Copy constructor
Copyable::Copyable(const Copyable & other) : instance_number_{ ++instance_count_ }
{
	// allocate array
	dummy_ptr_ = new int[array_size_];
	std::copy(other.dummy_ptr_, other.dummy_ptr_ + array_size_, 
		stdext::checked_array_iterator<int*>(dummy_ptr_, array_size_));

	std::cout << "Copyable #" << instance_number_ << ": Copy constructor, copying #" 
		<< other.instance_number_ << std::endl;
	// we do NOT want to copy the instance number, so we can better track which instances we are dealing with
}


Copyable::~Copyable()
{
	// free memory
	delete[] dummy_ptr_;
	std::cout << "Copyable #" << instance_number_ << ": Destructor" << std::endl;
}

Copyable & Copyable::operator=(const Copyable & other)
{
	if (&other != this) { // skip copying for self-assignment
		// copy data
		std::copy(other.dummy_ptr_, other.dummy_ptr_ + array_size_, 
			stdext::checked_array_iterator<int*>(dummy_ptr_, array_size_));
	}

	std::cout << "Copyable #" << instance_number_ << ": Assignment operator, assigning #" 
		<< other.instance_number_ << std::endl;

	// we do NOT want to copy the instance number, so we can better track which instances we are dealing with
	return *this;
}

//-------------------------------------------------------------------------------------------------
// some test methods to illustrate copying and moving
//-------------------------------------------------------------------------------------------------
Copyable create_copyable() {
	std::cout << "--- Start create_copyable" << std::endl;
	Copyable c; // this will call the default constructor
	std::cout << "--- End create_copyable" << std::endl;
	return c; // this will call the copy constructor and copy c to a 'temporary'. 
			  // It will NOT call a move constructor because the compiler will not generate a move constructor if you provide a copy constructor
}

Copyable play_with_copyable(Copyable c) { // calling this method will call the copy constructor, copying the instance passed to this method to variable c
	std::cout << "--- Start play_with_copyable" << std::endl;
	Copyable a{ c }; // copy constructor
	a = c; // copy assignment operator
	std::cout << "--- End play_with_copyable" << std::endl;
	return a; // this will call the copy constructor and copy c to a 'temporary'
}

void test_copyable() {
	std::cout << "--- Start Test Copyable" << std::endl;
	Copyable a; // this will call the copy constructor
	std::cout << "--- Call create_copyable" << std::endl;
	a = create_copyable(); // this will call the copy assignment operator, copying the return value of method create_copyable to a.
						   // it will NOT call a move asssignment operator, because the compiler will not generate one if you provide a copy assignment operator
	std::cout << "--- Returned from create_copyable, call play_with_copyable" << std::endl;
	a = play_with_copyable(a); // this will the copy assignment operator, copying the return value of method play_with_copyable to a.
	std::cout << "--- Returned from play_with_copyable" << std::endl;
}

