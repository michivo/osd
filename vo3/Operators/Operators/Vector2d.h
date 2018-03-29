#pragma once
#include <ostream>

class Vector2d
{
public:
	Vector2d();
	Vector2d(double x, double y);

	double get_x() const;
	double get_y() const;

	double euclidian_norm() const;

	Vector2d& operator+=(const Vector2d& rhs); // operators changing the value itself (like +=,...)
	Vector2d& operator-=(const Vector2d& rhs); // are members - others (like +, -,...) are
	Vector2d& operator*=(double rhs);          // non-members, see below
	Vector2d& operator/=(double rhs);

	explicit operator double() const; //[1] just for demo purposes - converts to the euclidian norm
	void operator()(); //[2] just for demo purposes - normalizes the vector

	friend std::ostream& operator<<(std::ostream& os, const Vector2d& rhs); // friend for printing
	                                                                        // to ostream like cout
private:
	double x_;
	double y_;
};

// here are the non-member operators. none of them changes a vector, they all return new instances
Vector2d operator+(Vector2d lhs, const Vector2d& rhs);
Vector2d operator-(Vector2d lhs, const Vector2d& rhs);

Vector2d operator-(Vector2d vec);

Vector2d operator*(double lhs, Vector2d rhs);
Vector2d operator/(double lhs, Vector2d rhs);
Vector2d operator*(Vector2d lhs, double rhs);
Vector2d operator/(Vector2d lhs, double rhs);