#pragma once

#include "IShape.h"
#include "Point2d.h"
#include "IClickable.h"

class Rect : public IShape, public IClickable {
public:
	Rect();

	Rect(double height, double width, Point2d center);

	void draw(ICanvas& canvas) const override;

	void scale(double factor) override;

	void move(double dx, double dy) override;

	double area() const override;

	double circumference() const override;

	virtual bool is_in_region(Point2d point) const override;

	virtual void handle_click(Point2d point) const override;


private:
	double height_;
	double width_;
	Point2d center_;

};
