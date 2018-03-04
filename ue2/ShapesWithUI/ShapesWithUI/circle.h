#pragma once
#include "Point2d.h"

#include <Windows.h>
#include <gdiplus.h>

class Circle
{
public:
	Circle();

	Circle(float radius, Point2d center);

	void draw(Gdiplus::Pen* pen, Gdiplus::Graphics& g);

	void scale(float factor);

	void move(float dx, float dy);

	double area() const;

	double circumference() const;

private:
	float radius_;

	Point2d center_;

	constexpr static double pi_ = 3.14159265358979323846;
};

