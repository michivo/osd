#include "stdafx.h"
#include "Point2d.h"

Point2d::Point2d(int x, int y) : x_{ x }, y_{ y }
{
}

int Point2d::x() const
{
	return x_;
}

int Point2d::y() const
{
	return y_;
}
