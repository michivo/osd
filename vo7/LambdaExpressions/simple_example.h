#pragma once
#include <functional>
#include <chrono>


void run_delayed(std::chrono::duration<double> delay, std::function<void()> func);

void simple_example();

