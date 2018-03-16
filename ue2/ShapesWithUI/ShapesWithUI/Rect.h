#pragma once

#include "IShape.h"
#include "Point2d.h"

class Rect : public IShape {
public:
	Rect();

	Rect(double height, double width, Point2d center);

	void draw(ICanvas& canvas) const override;

	void scale(double factor) override;

	void move(double dx, double dy) override;

	double area() const override;

	double circumference() const override;

private:
	double height_;
	double width_;
	Point2d center_;
};
