#pragma once
#include "Point2d.h"
#include "ICanvas.h"
#include "IShape.h"

class Circle : public IShape
{
public:
	Circle();

	Circle(double radius, Point2d center);

	void draw(ICanvas& canvas) const override;

	void scale(double factor) override;

	void move(double dx, double dy) override;

	double area() const override;

	double circumference() const override;

private:
	double radius_;

	Point2d center_;

	constexpr static double pi = 3.14159265358979323846;
};

