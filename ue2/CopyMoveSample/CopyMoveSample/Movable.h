#pragma once

// This class implements the "Rule of Five":
// It has a copy constructor, move constructor, destructor, copy assignment operator and move assignment operator

class Movable
{
public:
	// Default constructor
	Movable();

	// Declaraion of copy constructor
	Movable(const Movable& other);

	// Declaration of move constructor
	Movable(Movable&& other);

	// Declaration of desctructor
	~Movable();

	// Declaration of copy assignment operator
	Movable& operator=(const Movable& other);

	// Declaration of move assignment operator
	Movable& operator=(Movable&& other);

private:
	// this helps us count how many instances have already been created. We will discuss 'static' lateron
	// this is a so called 'static class member' - there is only one for all instances of this class.
	// it will count how many instances of this class have been created.
	static int instance_count_;

	// this is a normal member variable, each instance of this class has a distinct instance_number_. 
	// it will be 1 for the 1st instance created, 2 for the 2nd instance created, ...
	int instance_number_;

	// Just a dummy-pointer so there is something to allocate, copy and delete
	int* dummy_ptr_;

	// this will hold the array size for the array dummy_ptr_ points to
	static int array_size_;
};

void test_movable();
