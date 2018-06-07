#pragma once
#include <ostream>

template<typename T>
class Pair
{
public:
	Pair(T first, T second) : first_{ first }, second_{ second }
	{
	}

	T first() const
	{
		return first_;
	}

	T second() const
	{
		return second_;
	}

private:
	T first_;
	T second_;
};

template<typename T>
bool operator<(const Pair<T>& lhs, const Pair<T>& rhs)
{
	if (lhs.first() == rhs.first())
	{
		return lhs.second() < rhs.second();
	}

	return lhs.first() < rhs.first();
}

template<typename T>
std::ostream& operator<<(std::ostream& lhs, const Pair<T>& rhs)
{
	lhs << "(" << rhs.first() << ", " << rhs.second() << ")";
	return lhs;
}
