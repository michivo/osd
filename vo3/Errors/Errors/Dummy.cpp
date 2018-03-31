#include "stdafx.h"
#include "Dummy.h"

#include <iostream>
#include <vector>

Dummy::Dummy(int size) : values_(size)
{
	// this will create a new vector with [size] elements. but what, if size is < 0?
	std::cout << "Constructor called successfully!" << std::endl;
}

Dummy::Dummy(int size, int dummy)
{
	try {
		// This time, values_ is not created via initializer but in the constructor body.
		values_ = std::vector<int>(size, dummy);
		std::cout << "Constructor called successfully!" << std::endl;
	}
	catch(const std::exception&)
	{ // here we can handle the exeption, e.g. log it, modify it or find a way of fixing what went wrong
		std::cout << "Constructor failed!" << std::endl;
		throw; // but in this case, nothing can be done, we 'rethrow' the exception
	}
}


// bool parameter is just a dummy
Dummy::Dummy(int size, bool dummy) try : values_(size) // so called function-try-block
{
	// this will create a new vector with [size] elements. but what, if size is < 0?
	std::cout << "Constructor called successfully!" << std::endl;
}
catch(const std::exception&)
{ // here we can react to exceptions, usually we can log or modify the exception
	std::cout << "Constructor failed!" << std::endl;
	// but the exception will still be re-thrown here
}

Dummy::~Dummy()
{ // will never be called in our example since no instance has been created properly
	std::cout << "Destructor called!" << std::endl;
}
