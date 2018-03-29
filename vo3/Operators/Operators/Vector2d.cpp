#include "stdafx.h"
#include "Vector2d.h"
#include <complex>


Vector2d::Vector2d() : x_{ 0 }, y_{ 0 }
{
}

Vector2d::Vector2d(double x, double y) : x_{ x }, y_{ y }
{
}

double Vector2d::get_x() const
{
	return x_;
}

double Vector2d::get_y() const
{
	return y_;
}

double Vector2d::euclidian_norm() const
{
	return std::sqrt(x_*x_ + y_ * y_);
}

Vector2d& Vector2d::operator+=(const Vector2d& rhs)
{
	x_ += rhs.x_;
	y_ += rhs.y_;
	return *this;
}

Vector2d& Vector2d::operator-=(const Vector2d& rhs)
{
	x_ -= rhs.x_;
	y_ -= rhs.y_;
	return *this;
}

Vector2d& Vector2d::operator*=(double rhs)
{
	x_ *= rhs;
	y_ *= rhs;
	return *this;
}

Vector2d& Vector2d::operator/=(double rhs)
{
	x_ /= rhs;
	y_ /= rhs;
	return *this;
}

Vector2d operator-(Vector2d vec)
{
	vec *= -1;
	return vec;
}

Vector2d::operator double() const
{
	return euclidian_norm();
}

void Vector2d::operator()()
{
	const double norm = euclidian_norm();
	x_ /= norm;
	y_ /= norm;
}

Vector2d operator+(Vector2d lhs, const Vector2d& rhs)
{
	lhs += rhs;
	return lhs;
}

Vector2d operator-(Vector2d lhs, const Vector2d& rhs)
{
	lhs -= rhs;
	return lhs;
}

Vector2d operator*(double lhs, Vector2d rhs)
{
	rhs *= lhs;
	return rhs;
}

Vector2d operator/(double lhs, Vector2d rhs)
{
	rhs /= lhs;
	return rhs;
}

Vector2d operator*(Vector2d lhs, double rhs)
{
	lhs *= rhs;
	return lhs;
}

Vector2d operator/(Vector2d lhs, double rhs)
{
	lhs /= rhs;
	return lhs;
}


std::ostream& operator<<(std::ostream& os, const Vector2d& rhs)
{
	os << "(" << rhs.x_ << ", " << rhs.y_ << ")";
	return os;
}
