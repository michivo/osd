#include "stdafx.h"
#include "Pen.h"

namespace drawing {

	Pen::Pen() : color_{}, stroke_width_{ 1.0f }
	{
	}

	Pen::Pen(Color color, float stroke_width) : color_{ color }, stroke_width_{ stroke_width }
	{
	}

	Color Pen::get_color()
	{
		return color_;
	}

	float Pen::get_stroke_width()
	{
		return stroke_width_;
	}

}