#include "stdafx.h"
#include "SvgCanvas.h"

Svg_canvas::Svg_canvas(std::ostream& output) : output_{ output }
{
}

void Svg_canvas::write_header(int height, int width) const
{
	output_ << "<!DOCTYPE html>" << std::endl
		<< "<html>" << std::endl
		<< "<body>" << std::endl
		<< "<svg height=\"" << height << "\" width=\"" << width << "\">" << std::endl;
}

void Svg_canvas::draw_ellipse(Point2d center, double height, double width)
{
	output_ << "<ellipse rx=\"" << width / 2 << "\" ry=\"" << height / 2 << "\" "
		<< "cx=\"" << center.x << "\" cy=\"" << center.y << "\" style=\""
		<< "fill:rgb(127, 127, 255);stroke-width:2;stroke:rgb(0, 0, 0);fill-opacity:0.3;stroke-opacity:0.9\" />" << std::endl;
}

void Svg_canvas::draw_rectangle(Point2d top_left, double height, double width)
{
	output_ << "<rect width=\"" << width << "\" height=\"" << height << "\" "
		<< "x=\"" << top_left.x << "\" y=\"" << top_left.y << "\" style=\""
		<< "fill:rgb(64, 255, 0);stroke-width:2;stroke:rgb(0, 0, 0);fill-opacity:0.3;stroke-opacity:0.9\" />" << std::endl;
}

void Svg_canvas::draw_arc(Point2d center, double height, double width, double start_angle, double end_angle)
{
	// you can do this yourself, if you want to.
	// description for arcs can be found e.g. here https://developer.mozilla.org/en-US/docs/Web/SVG/Tutorial/Paths
}

void Svg_canvas::write_footer() const
{
	output_ << "</svg>" << std::endl
		<< "</body>" << std::endl
		<< "</html>" << std::endl;
}
