#pragma once

#include "Point2d.h"
#include "IDrawableShape.h"

class Rect : public IDrawableShape {
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
