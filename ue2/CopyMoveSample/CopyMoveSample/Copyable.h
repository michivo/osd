#pragma once

// This class implements the "Rule of Three":
// It has a copy constructor, destructor and copy assignment operator

class Copyable
{
public:
	// Default constructor
	Copyable();
	
	// Declaraion of copy constructor
	Copyable(const Copyable& other);

	// Declaration of desctructor
	~Copyable();

	// Declaration of copy assignment operator
	Copyable& operator=(const Copyable& other);

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

// here we declare a test function that will just do some creating, copying, assigning, ...
void test_copyable();