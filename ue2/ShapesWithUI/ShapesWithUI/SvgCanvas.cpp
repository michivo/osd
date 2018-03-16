#include "stdafx.h"
#include "SvgCanvas.h"

#include <iostream>

SvgCanvas::SvgCanvas(std::ostream & stream) : stream_{stream}
{
}

void SvgCanvas::start_drawing()
{
	stream_ << "<!DOCTYPE html>" << std::endl
		<< "<html>" << std::endl
		<< "<body>" << std::endl
		<< "<svg height=\"1000\" width=\"1000\">" << std::endl;
}

void SvgCanvas::draw_ellipse(Point2d center, double height, double width)
{
	stream_ << "<ellipse rx=\"" << width / 2 << "\" ry=\"" << height / 2 << "\" "
		<< "cx=\"" << center.x << "\" cy=\"" << center.y << "\" style=\""
		<< "fill:rgb(255, 127, 255);stroke-width:2;stroke:rgb(0, 0, 0);fill-opacity:0.3;stroke-opacity:0.9\" />" << std::endl;
}

void SvgCanvas::draw_rectangle(Point2d top_left, double height, double width)
{
	stream_ << "<rect width=\"" << width << "\" height=\"" << height << "\" "
		<< "x=\"" << top_left.x << "\" y=\"" << top_left.y << "\" style=\""
		<< "fill:rgb(127, 127, 255);stroke-width:2;stroke:rgb(0, 0, 0);fill-opacity:0.3;stroke-opacity:0.9\" />" << std::endl;
}

void SvgCanvas::draw_arc(Point2d center, double height, double width, double start_angle, double end_angle)
{
}

void SvgCanvas::finish_drawing()
{
	stream_ << "</svg>" << std::endl
		<< "</body>" << std::endl
		<< "</html>" << std::endl;
}
