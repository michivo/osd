#pragma once

#include "Point2d.h"

class ICanvas {
public:
	virtual void draw_ellipse(Point2d center, double height, double width) = 0;

	virtual void draw_rectangle(Point2d top_left, double height, double width) = 0;

	virtual void draw_arc(Point2d center, double height, double width, double start_angle, double end_angle) = 0;

	virtual ~ICanvas() = 0;
};