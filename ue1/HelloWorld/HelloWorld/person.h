#pragma once

#include <string>

using namespace std;

class Person
{
public:
	Person(); // default constructor

	Person(int age, string first_name, string last_name);

	int get_age() const; // 'const' says that this method does not modify our object

	void set_age(int age); // no 'const' - this will modify our object!

	string get_first_name() const;

	string get_last_name() const;

	string get_full_name() const;

private:
	int age_; // underscore at the end to mark member variables - this avoids confusion with constructor/method parameters
	string first_name_;
	string last_name_;

};

