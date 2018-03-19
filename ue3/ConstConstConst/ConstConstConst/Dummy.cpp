#include "stdafx.h"
#include "Dummy.h"

Dummy::Dummy() : od_{ 0 } {
}

Dummy::Dummy(OtherDummy od) : od_{ od }
{
}

const OtherDummy & Dummy::get_other_ref() const
{
	return od_;
}

OtherDummy Dummy::get_other_val() const
{
	return od_;
}

OtherDummy& Dummy::get_other_nc_ref()
{
	return od_;
}

void Dummy::set_other(const OtherDummy & od)
{
	od_ = od;
}

void Dummy::change_dummy(int new_x)
{
	od_.set_x(new_x);
}

void Dummy::const_change_dummy(int new_x) const
{
	// od_.set_x(new_x); // compiler says no. cannot call non-const method on member in const method
}
