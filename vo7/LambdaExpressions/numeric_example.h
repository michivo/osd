#pragma once
#include <vector>
#include <functional>

int aggregate(std::vector<int> numbers, std::function<int(int, int)> aggregator, int seed = 0);

void numeric_example();
