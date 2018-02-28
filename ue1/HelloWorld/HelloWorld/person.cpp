#include "stdafx.h"
#include "person.h"

// implementation of default constructor
Person::Person() : age_{ 20 }, first_name_{ "Max" }, last_name_{ "Mustermann" }
{
}

Person::Person(int age, string first_name, string last_name) :
	age_{ age },
	first_name_{ first_name },
	last_name_{ last_name }
{
}

int Person::get_age() const
{
	return age_;
}

void Person::set_age(int age)
{
	age_ = age;
}

string Person::get_first_name() const
{
	return first_name_;
}

string Person::get_last_name() const
{
	return last_name_;
}

string Person::get_full_name() const
{
	return first_name_ + " " + last_name_;
}

