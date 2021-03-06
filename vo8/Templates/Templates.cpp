// Templates.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Pair.h"

#include <vector>
#include <iostream>
#include <string>
#include "TemplateFilters.h"

template<typename Iterator>
void swap(Iterator one, Iterator other) {
	auto temp = *one;
	*one = *other;
	*other = temp;
}

template<typename T>
void sort(std::vector<T>& values) {

	for (unsigned int idx1 = 0; idx1 < values.size() - 1; ++idx1) {
		bool sorted = true;
		for (unsigned int idx2 = 0; idx2 < values.size() - idx1 - 1; ++idx2) {
			if (values[idx2 + 1] < values[idx2]) {
				sorted = false;
				swap(values.begin() + idx2, values.begin() + idx2 + 1);
			}
		}
		if (sorted)
			break;
	}
}

template<typename T>
void print(std::vector<T>& values) {
	for (auto x : values) {
		std::cout << x << " - ";
	}
	std::cout << std::endl;
}

int main()
{
	std::vector<int> numbers = { 9, 6, 2, 1, 3, 4, 5, 8, 7 };
	std::vector<double> doubles = { 1, 3.14, 1.41421356237, 1.7320508, 2, 2.236067977 };
	std::vector<std::string> strings = { "Polster", "Neuhold", "Soukup", "Mark", "Netta", "Dauer" };

	sort(numbers);
	print(numbers);
	sort(strings);
	print(strings);
	sort(doubles);
	print(doubles);

	const Pair<int> p{ 2, 3 };
	const Pair<int> next{ 1, 4 };
	std::vector<Pair<int>> pairs{ p, next };
	sort(pairs);
	print(pairs);

	const Pair<std::string> p1{ "Loesel", "Lampee" };
	const Pair<std::string> p2{ "Kemperle", "Winkler" };
	std::vector<Pair<std::string>> more_pairs{ p1, p2 };
	print(more_pairs);
	sort(more_pairs);
	print(more_pairs);

	filter_demo();
	getchar();
	return 0;
}

