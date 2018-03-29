#pragma once

class Point2d final
{
public:
	Point2d(int x, int y);

	int x() const;
	int y() const;
	
private:
	int x_;
	int y_;
};

