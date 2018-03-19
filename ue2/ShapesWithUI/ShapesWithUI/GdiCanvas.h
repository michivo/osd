#pragma once

#include "Point2D.h"
#include "ICanvas.h"

#include <gdiplus.h>
#include <memory>

class Gdi_canvas : public ICanvas {
public:
	Gdi_canvas(std::shared_ptr<Gdiplus::Graphics> graphics, std::shared_ptr<Gdiplus::Pen> pen);

	virtual void draw_ellipse(Point2d center, double height, double width) override;

	virtual void draw_rectangle(Point2d top_left, double height, double width) override;

	virtual void draw_arc(Point2d center, double height, double width, double start_angle, double end_angle) override;

private:
	std::shared_ptr<Gdiplus::Graphics> graphics_;
	std::shared_ptr<Gdiplus::Pen> pen_;
};
