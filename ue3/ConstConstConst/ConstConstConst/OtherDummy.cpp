#include "stdafx.h"
#include "OtherDummy.h"

OtherDummy::OtherDummy(int x) : x_{ x }
{
}

int OtherDummy::get_x() const
{
	return x_;
}

void OtherDummy::set_x(int x)
{
	x_ = x;
}
