#include "stdafx.h"

#include "Circle.h"
#include "Point2d.h"
#include "ICanvas.h"
#include <stdexcept>

Circle::Circle() : radius_{ 1 }, center_{ 0,0 }
{
}

Circle::Circle(double radius, Point2d center) : radius_{ radius }, center_{ center }
{
	if (radius_< 0)
		throw std::invalid_argument("Radius must not be smaller than zero!");
}

void Circle::draw(ICanvas& canvas) const
{
	canvas.draw_ellipse(center_, 2 * radius_, 2 * radius_);
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
	return radius_ * radius_ * pi;
}

double Circle::circumference() const
{
	return 2 * radius_ * pi;
}
