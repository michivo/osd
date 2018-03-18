#include "stdafx.h"

#include "Rect.h"
#include "Point2d.h"
#include "IShape.h"

#include <iostream>

Rect::Rect() : height_{ 1 }, width_{ 1 }, center_{ 0,0 }
{}

Rect::Rect(double height, double width, Point2d center) :
	height_{ height }, width_{ width }, center_{ center }
{
}

void Rect::draw(ICanvas & canvas) const
{
	canvas.draw_rectangle({ center_.x - width_ / 2, center_.y - height_ / 2 }, width_, height_);
}

void Rect::scale(double factor)
{
	height_ *= factor;
	width_ *= factor;
}

void Rect::move(double dx, double dy)
{
	center_ = Point2d{ center_.x + dx, center_.y + dy };
}

double Rect::area() const
{
	return 0.0;
}

double Rect::circumference() const
{
	return 0.0;
}

bool Rect::is_in_region(Point2d point) const
{
	if (point.x < (center_.x - width_ / 2) || point.x > (center_.x + width_ / 2)) {
		return false;
	}

	if (point.y < (center_.y - height_ / 2) || point.y >(center_.y + height_ / 2)) {
		return false;
	}

	return true;
}

void Rect::handle_click(Point2d point) const
{
	std::cout << "Rectangle was clicked!" << std::endl;
}
