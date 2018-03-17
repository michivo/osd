#include "stdafx.h"

#include "circle.h"
#include "Point2d.h"
#include "ICanvas.h"
#include "IFancyCanvas.h"
#include "Pen.h"

Circle::Circle() : radius_{ 1 }, center_{ 0,0 }
{
}

Circle::Circle(double radius, Point2d center) : radius_{ radius }, center_{ center }
{
}

void Circle::draw(ICanvas& canvas) const
{
	canvas.draw_ellipse(center_, 2 * radius_, 2 * radius_);
}

void Circle::draw(IFancy_canvas & canvas) const
{
	canvas.draw_ellipse(drawing::Pen{ {123, 123, 123}, 5 }, center_, 2 * radius_, 2 * radius_);
}

void Circle::scale(double factor)
{
	radius_ *= factor;
}

void Circle::move(double dx, double dy)
{
	center_.x += dx;
	center_.y += dy;
}

double Circle::area() const
{
	return radius_ * radius_ * pi_;
}

double Circle::circumference() const
{
	return 2 * radius_ * pi_;
}
