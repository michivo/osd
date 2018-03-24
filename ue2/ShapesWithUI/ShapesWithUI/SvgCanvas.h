#pragma once
#include "ICanvas.h"
#include <ostream>

class Svg_canvas : public ICanvas
{
public:
	Svg_canvas(std::ostream& output);

	void write_header(int height, int width) const;

	void draw_ellipse(Point2d center, double height, double width) override;

	void draw_rectangle(Point2d top_left, double height, double width) override;

	void draw_arc(Point2d center, double height, double width, double start_angle, double end_angle) override;

	void write_footer() const;

private:
	std::ostream& output_;
};
