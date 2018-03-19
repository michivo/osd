#include "stdafx.h"

#include "Rect.h"
#include "Point2d.h"
#include "IShape.h"

Rect::Rect() : height_{ 1 }, width_{ 1 }, center_{ 0,0 }
{
}

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
	return height_ * width_;
}

double Rect::circumference() const
{
	return 2 * (height_ + width_);
}
