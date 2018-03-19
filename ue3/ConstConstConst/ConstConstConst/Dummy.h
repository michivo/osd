#pragma once

#include "OtherDummy.h"

class Dummy
{
public:
	Dummy();

	Dummy(OtherDummy od);

	const OtherDummy& get_other_ref() const; // const method returning reference-to-const

	OtherDummy get_other_val() const; // const method returning copy

	OtherDummy& get_other_nc_ref(); // method returning non-const reference - works. 
									// method must not be const, since it returns non-const reference and allows access to internals

	void set_other(const OtherDummy& od); // reference-to-const is passed, od must not be changed!

	void change_dummy(int new_x); // this will work, non-const method may call non-const methods on member variables

	void const_change_dummy(int new_x) const; // this will not work! const cannot call non-const methods on member variables!

private:
	OtherDummy od_;
};

