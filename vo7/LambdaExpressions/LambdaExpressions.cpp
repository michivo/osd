// LambdaExpressions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "numeric_example.h"
#include "simple_example.h"
#include "capture_example.h"
#include "class_example.h"


int main()
{
	simple_example();
	numeric_example();
	capture_example();
	class_example();
	getchar();
    return 0;
}

