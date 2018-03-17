#include "stdafx.h"
#include "GdiCanvas.h"
#include "Pen.h"
#include "Color.h"

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

void Gdi_canvas::draw_ellipse(drawing::Pen pen, Point2d center, double height, double width)
{
	graphics_->DrawEllipse(map_pen(pen).get(), static_cast<Gdiplus::REAL>(center.x - width / 2.0),
		static_cast<Gdiplus::REAL>(center.y - height / 2.0),
		static_cast<Gdiplus::REAL>(width),
		static_cast<Gdiplus::REAL>(height));
}

void Gdi_canvas::draw_rectangle(drawing::Pen pen, Point2d top_left, double height, double width)
{
	graphics_->DrawRectangle(map_pen(pen).get(),
		static_cast<Gdiplus::REAL>(top_left.x),
		static_cast<Gdiplus::REAL>(top_left.y),
		static_cast<Gdiplus::REAL>(width),
		static_cast<Gdiplus::REAL>(height));
}

void Gdi_canvas::draw_arc(drawing::Pen pen, Point2d center, double height, double width, double start_angle, double end_angle)
{
	graphics_->DrawArc(map_pen(pen).get(), static_cast<Gdiplus::REAL>(center.x - width / 2.0),
		static_cast<Gdiplus::REAL>(center.y - height / 2.0),
		static_cast<Gdiplus::REAL>(width),
		static_cast<Gdiplus::REAL>(height),
		static_cast<Gdiplus::REAL>(start_angle),
		static_cast<Gdiplus::REAL>(end_angle));
}

std::unique_ptr<Gdiplus::Pen> Gdi_canvas::map_pen(drawing::Pen pen)
{
	auto color = pen.get_color();
	Gdiplus::Color c{ color.A, color.R, color.G, color.B };

	return std::unique_ptr<Gdiplus::Pen>(new Gdiplus::Pen{ c, pen.get_stroke_width() });
}
