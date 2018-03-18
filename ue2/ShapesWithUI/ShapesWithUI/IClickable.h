#pragma once

#include "Point2D.h"

#include <functional>

class IClickable {
public:
	virtual bool is_in_region(Point2d point) const = 0;

	virtual void handle_click(Point2d point) const = 0;

	virtual ~IClickable() = 0;
};