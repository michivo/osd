#include "stdafx.h"
#include "GdiCanvas.h"

#include <memory>

Gdi_canvas::Gdi_canvas(std::shared_ptr<Gdiplus::Graphics> graphics,
	std::shared_ptr<Gdiplus::Pen> pen) : graphics_{graphics}, pen_{pen}
{
}

void Gdi_canvas::draw_ellipse(Point2d center, double height, double width)
{
	graphics_->DrawEllipse(pen_.get(), static_cast<Gdiplus::REAL>(center.x - width/2.0),
		static_cast<Gdiplus::REAL>(center.y - height/2.0),
		static_cast<Gdiplus::REAL>(width),
		static_cast<Gdiplus::REAL>(height));
}

void Gdi_canvas::draw_rectangle(Point2d top_left, double height, double width)
{
	graphics_->DrawRectangle(pen_.get(),
		static_cast<Gdiplus::REAL>(top_left.x),
		static_cast<Gdiplus::REAL>(top_left.y),
		static_cast<Gdiplus::REAL>(width),
		static_cast<Gdiplus::REAL>(height));
}

void Gdi_canvas::draw_arc(Point2d center, double height, double width, double start_angle, double sweep_angle)
{
	graphics_->DrawArc(pen_.get(), static_cast<Gdiplus::REAL>(center.x - width / 2.0),
		static_cast<Gdiplus::REAL>(center.y - height / 2.0),
		static_cast<Gdiplus::REAL>(width),
		static_cast<Gdiplus::REAL>(height),
		static_cast<Gdiplus::REAL>(start_angle),
		static_cast<Gdiplus::REAL>(sweep_angle));
}
