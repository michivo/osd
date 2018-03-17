#pragma once

#include "Color.h"

#include <cstdint>

namespace drawing {
	class Pen {
	public:
		Pen();

		Pen(Color color, float stroke_width);

		Color get_color();

		float get_stroke_width();

	private:
		Color color_;

		float stroke_width_;
	};
}
