// StaticDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CountingThing.h"
#include <iostream>


void print_stats(const counting_thing& thing)
{
	std::cout << "This is instance " << thing.instance_number() << ", there are currently "
		<< counting_thing::current_instances() << " instances alive of the total "
		<< counting_thing::total_instances() << " ever created" << std::endl;
}

counting_thing copy_thing(counting_thing other)
{
	return other;
}

int main()
{
	counting_thing thing;
	print_stats(thing);
	counting_thing other = thing;
	print_stats(other);
	std::swap(thing, other);
	print_stats(other);
	thing = copy_thing(other);
	print_stats(thing);
	const counting_thing third;
	print_stats(third);

    return 0;
}

