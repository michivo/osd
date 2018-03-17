#pragma once

#include "Pen.h"
#include "ICanvas.h"

class IFancy_canvas : public ICanvas {
public:
	virtual void draw_ellipse(drawing::Pen pen, Point2d center, double height, double width) = 0;

	virtual void draw_rectangle(drawing::Pen pen, Point2d top_left, double height, double width) = 0;

	virtual void draw_arc(drawing::Pen pen, Point2d center, double height, double width, double start_angle, double end_angle) = 0;
};
