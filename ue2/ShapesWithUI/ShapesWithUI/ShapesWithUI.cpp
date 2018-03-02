// ShapesWithUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DrawingWindow.h"

#include <vector>
#include <memory>


int main()
{
	std::vector<std::shared_ptr<Circle>> circles;
	circles.push_back(std::make_shared<Circle>(Circle{ 50, Point2d{ 50, 50 } }));
	circles.push_back(std::make_shared<Circle>(Circle{ 60, Point2d{ 100, 100 } }));
	circles.push_back(std::make_shared<Circle>(Circle{ 40, Point2d{ 50, 30 } }));
	circles.push_back(std::make_shared<Circle>(Circle{ 30, Point2d{ 120, 100 } }));
	circles.push_back(std::make_shared<Circle>(Circle{ 77, Point2d{ 150, 50 } }));
	circles.push_back(std::make_shared<Circle>(Circle{ 90, Point2d{ 10, 100 } }));
	circles.push_back(std::make_shared<Circle>(Circle{ 10, Point2d{ 520, 50 } }));
	circles.push_back(std::make_shared<Circle>(Circle{ 5, Point2d{ 200, 100 } }));
	DrawingWindow::Window w;
	w.show(circles);
    return 0;
}

