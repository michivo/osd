#pragma once
#include "Point2d.h"
#include "ICanvas.h"
#include "IShape.h"

#include <Windows.h>
#include <gdiplus.h>
#include <iostream>

class Circle : public IShape
{
public:
	Circle();

	Circle(double radius, Point2d center);

	void draw(ICanvas& canvas) const;

	void scale(double factor);

	void move(double dx, double dy);

	double area() const;

	double circumference() const;

private:
	double radius_;

	Point2d center_;

	constexpr static double pi_ = 3.14159265358979323846;
};

