#pragma once

#include "ICanvas.h"

class IShape {
public:
	virtual void scale(double factor) = 0;

	virtual void move(double dx, double dy) = 0;

	virtual double area() const = 0;

	virtual double circumference() const = 0;

	virtual ~IShape() = 0;
};
