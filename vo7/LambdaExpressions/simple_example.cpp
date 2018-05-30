#include "stdafx.h"
#include "simple_example.h"

#include <thread>
#include <chrono>
#include <iostream>

void run_delayed(std::chrono::duration<double> delay, std::function<void()> func)
{
	std::this_thread::sleep_for(delay);
	func();
}

void simple_example()
{
	using namespace std::chrono_literals;

	run_delayed(10ms, []() {std::cout << "One!\n"; });
	run_delayed(20ms, [] {std::cout << "Two!\n"; }); // braces are optional if there are no params
	run_delayed(40ms, [] () noexcept {std::cout << "Three!\n"; }); // may be noexcept

	std::thread bye_thread(run_delayed, 100ms, []() {std::cout << "Four!\n"; }); // will probably be printed at the end of the program
	bye_thread.detach();
}
