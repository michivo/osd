#include "stdafx.h"
#include "simple_example.h"

#include <thread>
#include <chrono>
#include <iostream>

void run_delayed(std::chrono::duration<double> delay, std::function<void()> func)
{ // waits for a given amount of time, then calls the function passed to this method
	std::this_thread::sleep_for(delay);
	func();
}

std::function<void()> create_func()
{
	return [] {std::cout << "One point five!\n"; };
}

void say_something()
{
	std::cout << "Two point five!\n";
}

void simple_example()
{
	using namespace std::chrono_literals;

	run_delayed(10ms, []() {std::cout << "One!\n"; });
	run_delayed(10ms, create_func());
	run_delayed(10ms, [] {std::cout << "Two!\n"; }); // braces are optional if there are no params
	run_delayed(10ms, say_something); // a std::function can be created from a normal function like say_something, too
	run_delayed(10ms, [] () noexcept {std::cout << "Three!\n"; }); // may be noexcept

	std::thread bye_thread(run_delayed, 100ms, []() {std::cout << "Four!\n"; }); // will probably be printed at the end of the program
	bye_thread.detach();
}
