#pragma once

#include "ICanvas.h"
#include "IFancyCanvas.h"

class IShape {
public:
	virtual void draw(ICanvas& canvas) const = 0;

	virtual void draw(IFancy_canvas& canvas) const = 0;

	virtual void scale(double factor) = 0;

	virtual void move(double dx, double dy) = 0;

	virtual double area() const = 0;

	virtual double circumference() const = 0;

	virtual ~IShape() = 0;
};
