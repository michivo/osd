// CopyMoveSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Copyable.h"
#include "Movable.h"

#include <iostream>


int main()
{
	test_copyable();
	std::cout << std::endl << "-----------------------------------------------------------------" << std::endl << std::endl;
	test_movable();
	getchar();
    return 0;
}

