#pragma once

#include "ICanvas.h"

#include <iostream>

class SvgCanvas : public ICanvas {
public:
	SvgCanvas(std::ostream& stream);

	void start_drawing();
	
	void draw_ellipse(Point2d center, double height, double width) override;

	void draw_rectangle(Point2d top_left, double height, double width) override;

	void draw_arc(Point2d center, double height, double width, double start_angle, double end_angle) override;

	void finish_drawing();

private:
	std::ostream& stream_;
};

