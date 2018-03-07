// ShapesWithUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GdiWindow.h"

#include <vector>
#include <memory>

int main()
{
	std::vector<std::shared_ptr<Circle>> circles;
	for (int i = 0; i < 100; i++) {
		circles.push_back(std::make_shared<Circle>(Circle{
			static_cast<double>((3 * i + i*i*i + 22) % 227), // just some random numbers so we get a bunch of fine circles
			Point2d{ static_cast<double>((31 * i + 17) % 1234),
			static_cast<double>((37 * i + i*i + 19) % 807)} }));
	}

	GdiWindow w;
	w.show(circles);
	return 0;
}

