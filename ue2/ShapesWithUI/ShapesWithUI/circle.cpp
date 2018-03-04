#include "stdafx.h"

#include "circle.h"
#include "Point2d.h"

Circle::Circle() : radius_{ 1 }, center_{ 0,0 }
{
}

Circle::Circle(float radius, Point2d center) : radius_{ radius }, center_{ center }
{
}

void Circle::draw(Gdiplus::Pen* pen, Gdiplus::Graphics& g)
{
	g.DrawEllipse(pen, center_.x - radius_, center_.y - radius_, 2.0 * radius_, 2.0 * radius_);
}

void Circle::scale(float factor)
{
	radius_ *= factor;
}

void Circle::move(float dx, float dy)
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
