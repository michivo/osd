// ConstConstConst.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Dummy.h"

#include <iostream>
#include <vector>

using namespace std;

void reference_to_const(const int& val); // reference to a const value, value cannot be changed
void reference_to_non_const(int& val); // reference to a non-const value, value may be changed
void reference_to_const(const Dummy& val); // reference to a const value, value cannot be changed
void reference_to_non_const(Dummy& val); // reference to a non-const value, value may be changed

void const_value(const Dummy val); // const value - may not be changed, non-const-methods must not be called!
								   // Since val is copied when being passed, this is only to make sure you don't
								   // do anything you didn't want to in your method.

void non_const_value(Dummy val); // non-const value, may be changed, non-const-methods may be called!

void pointer_to_const(const Dummy* val); // pointer to const value, value cannot be changed
void pointer_to_const2(Dummy const* val); // pointer to const value, value cannot be changed, equivalent to method above
void pointer_to_non_const(Dummy* val); // pointer to non-const value, value may be changed
void const_pointer(Dummy* const val); // const pointer to non-const value, value may be changed but pointer must not be changed!
void const_pointer_to_const(const Dummy* const val); // const pointer to const value, neither value nor pointer may be changed!


// all const:
// - pointer to vector must not be changed
// - vector itself must not be changed (push_back,... not possible)
// - values in vector must not be changed
void const_pointer_to_const_vector_of_pointers_to_const_dummies(const vector<const Dummy*>* const dummies);

int main()
{
	Dummy d1{ OtherDummy{2} };
	Dummy ds[2];
	ds[0] = d1;
	ds[1] = Dummy{ OtherDummy{3} };

	int x = 99;
	const int& ref_to_const = x;
	// const_ref = 27; // no, not allowed on reference to const
	x = 27; // still possible! value behind ref changes, too!
	cout << x << " " << ref_to_const << endl;
	reference_to_const(x);
	reference_to_const(ref_to_const);
	reference_to_non_const(x);
	// reference_to_non_const(ref_to_const); // not possible to pass ref to const when ref to non const is required

	reference_to_const(d1);
	reference_to_non_const(d1);

	const_value(d1);
	non_const_value(d1);

	pointer_to_const(ds);
	pointer_to_const2(ds);
	pointer_to_non_const(ds);
	const_pointer(ds);
	const_pointer_to_const(ds);

	vector<const Dummy*> dummies;
	dummies.push_back(ds);
	dummies.push_back(ds);
	const_pointer_to_const_vector_of_pointers_to_const_dummies(&dummies);

	getchar();
	return 0;
}

void reference_to_const(const int& val) {
	// val = 42; // not allowed, val is reference-to-const!
	cout << val << endl; // reading is always ok!
}

void reference_to_non_const(int& val)
{
	val = 43; // allowed, this is not a reference-to-const
	cout << val << endl; // reading is always ok!
}

void reference_to_const(const Dummy& val)
{
	// val.set_other({ 1 }); // method is not const, cannot be called on reference-to-const
	// cout << val.get_other_nc_ref().get_x() << endl; // method is not const, cannot be called on reference-to-const
	cout << val.get_other_ref().get_x() << endl; // calling const methods is always ok!
}

void reference_to_non_const(Dummy & val)
{
	val.set_other({ 1 }); // method is not const, may be called on non-const-reference
	cout << val.get_other_nc_ref().get_x() << endl; // method is not const, may be called on non-const-reference
	cout << val.get_other_ref().get_x() << endl; // calling const methods is always ok!
}

void const_value(const Dummy val)
{
	// val.set_other({ 1 }); // method is not const, cannot be called on const value
	// cout << val.get_other_nc_ref().get_x() << endl; // method is not const, cannot be called on const value
	cout << val.get_other_ref().get_x() << endl; // calling const methods is always ok!
}

void non_const_value(Dummy val)
{
	val.set_other({ 77 }); // method is not const, may be called on non-const value
	cout << val.get_other_nc_ref().get_x() << endl; // method is not const, may be called on non-const value
	cout << val.get_other_ref().get_x() << endl; // calling const methods is always ok!
}

void pointer_to_const(const Dummy* val)
{
	val++; // setting pointer to next address is ok!
	// val->set_other({ 1 }); // method is not const, cannot be called on pointer to const
	// cout << val->get_other_nc_ref().get_x() << endl; // method is not const, cannot be called on pointer to const
	cout << val->get_other_ref().get_x() << endl; // calling const methods is always ok!
}

void pointer_to_const2(Dummy const * val)
{
	val++; // setting pointer to next address is ok!
	// val->set_other({ 1 }); // method is not const, cannot be called on pointer to const
	// cout << val->get_other_nc_ref().get_x() << endl; // method is not const, cannot be called on pointer to const
	cout << val->get_other_ref().get_x() << endl; // calling const methods is always ok!
}

void pointer_to_non_const(Dummy * val)
{
	val++; // setting pointer to next address is ok!
	val->set_other({ 99 }); // method is not const, can be called on pointer to non-const
	cout << val->get_other_nc_ref().get_x() << endl; // method is not const, can be called on pointer to non-const
	cout << val->get_other_ref().get_x() << endl; // calling const methods is always ok!
}

void const_pointer(Dummy * const val)
{
	// val++; // setting pointer to next address is not ok for const pointer, even if pointing to non-const
	val->set_other({ 55 }); // method is not const, can be called on const pointer to non-const
	cout << val->get_other_nc_ref().get_x() << endl; // method is not const, can be called on const pointer to non-const
	cout << val->get_other_ref().get_x() << endl; // calling const methods is always ok!
}

void const_pointer_to_const(const Dummy * const val)
{
	// val++; // setting pointer to next address is not ok for const pointer
	// val->set_other({ 99 }); // method is not const, cannot be called on pointer to const
	// cout << val->get_other_nc_ref().get_x() << endl; // method is not const, cannot be called on pointer to const
	cout << val->get_other_ref().get_x() << endl; // calling const methods is always ok!
}

void const_pointer_to_const_vector_of_pointers_to_const_dummies(const vector<const Dummy*>* const dummies)
{
	//dummies->clear(); // not possible on pointer to const
	cout << dummies->size() << endl; // we can do that! we cannot do much, but we can do that!

	// dummies = nullptr; // not possible on const pointer

	for (const Dummy* dummy : *dummies) {
		// dummy->set_other({ 4 }); // cannot call non-const method on pointer-to-const
		cout << dummy->get_other_val().get_x() << endl;
	}
}


