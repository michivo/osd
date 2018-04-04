#pragma once
#include <stdexcept>
#include <iostream>
#include <vector>

// you should not write code like this (multiple classes in one header, all code in header)
// in this case, I chose to put it all in one file to make it clearer what happens

class Base_first
{
public:
	Base_first(int x)
	{
		std::cout << "Base_first constructor" << std::endl;

		if (x % 5 == 0)
			throw std::logic_error("Base_first: 5 is bad!");
	}

	~Base_first()
	{
		std::cout << "Base_first destructor" << std::endl;
	}
};

class Base_second
{
public:
	Base_second(int x)
	{
		std::cout << "Base_second constructor" << std::endl;

		if (x % 3 == 0)
			throw std::logic_error("Base_second: 3 is bad!");
	}

	~Base_second()
	{
		std::cout << "Base_second destructor" << std::endl;
	}
};

class Member_first
{
public:
	Member_first(int x)
	{
		std::cout << "Member_first constructor" << std::endl;

		if (x % 7 == 0)
			throw std::logic_error("Member_first: 7 is bad!");
	}

	~Member_first()
	{
		std::cout << "Member_first destructor" << std::endl;
	}
};

class Member_second
{
public:
	Member_second(int x)
	{
		std::cout << "Member_second constructor" << std::endl;

		if (x % 11 == 0)
			throw std::logic_error("Member_second: 11 is bad!");
	}

	~Member_second()
	{
		std::cout << "Member_second destructor" << std::endl;
	}
};

class Combined : public Base_first, public Base_second
{
public:
	// even though we mention second before first, first will be initialized before first. 
	// you should not do this. For the sake of clarity, use the same order as in the base classes and field definitions!
	Combined(int x) : Base_second{ x }, Base_first{ x }, second_{ x }, first_{ x }
	{
		std::cout << "Combined constructor" << std::endl;

		if (x % 13 == 0)
			throw std::logic_error("Combined: 13 is bad!");
	}

	~Combined()
	{
		std::cout << "Combined destructor" << std::endl;
	}

private:
	Member_first first_;
	Member_second second_;
};