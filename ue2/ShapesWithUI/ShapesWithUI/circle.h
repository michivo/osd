#pragma once
#include "Point2d.h"

#include <Windows.h>
#include <gdiplus.h>

class Circle
{
public:
	Circle();

	Circle(double radius, Point2d center);

	void draw(Gdiplus::Pen* pen, Gdiplus::Graphics* g);

	void scale(double factor);

	void move(double dx, double dy);

	double area() const;

	double circumference() const;

private:
	double radius_;

	Point2d center_;

	constexpr static double pi_ = 3.14159265358979323846;
};

