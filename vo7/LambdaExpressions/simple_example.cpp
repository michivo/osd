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

	run_delayed(100ms, []() {std::cout << "Hello world!\n"; });
}