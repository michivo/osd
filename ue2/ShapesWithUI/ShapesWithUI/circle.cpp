#include "stdafx.h"

#include "circle.h"
#include "Point2d.h"

Circle::Circle() : radius_{ 1 }, center_{ 0,0 }
{
}

Circle::Circle(double radius, Point2d center) : radius_{ radius }, center_{ center }
{
}

void Circle::draw(Gdiplus::Pen* pen, Gdiplus::Graphics* g)
{
	g->DrawEllipse(pen, static_cast<Gdiplus::REAL>(center_.x - radius_), 
		static_cast<Gdiplus::REAL>(center_.y - radius_), 
		static_cast<Gdiplus::REAL>(2.0 * radius_), 
		static_cast<Gdiplus::REAL>(2.0 * radius_));
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
