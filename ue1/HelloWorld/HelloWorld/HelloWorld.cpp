// HelloWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "person.h"

#include <iostream>
#include <string>
#include <sstream>

int main()
{
	cout << "Hello! Enter your first name, last name and age:" << endl;

	string input;
	string first_name;
	string last_name;
	int age;

	getline(cin, input); // read user input from cin into variable input - dealing with newline and cin is a bit messy
	stringstream in_str{ input }; // create a string stream to process the input

	if (in_str >> first_name >> last_name >> age) { // process input and check if it was ok
		Person me{ age, first_name, last_name }; // create a new instance of class 'Person'
		cout << "Hello " << me.get_full_name() << ", you are " << me.get_age() << " years old.";
	}
	else {
		cout << "This was not a valid input!" << endl;
	}

	getchar(); // just so the debugger does not close our application immediately
	return 0;
}

