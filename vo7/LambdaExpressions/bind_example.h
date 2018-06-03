#pragma once

class Holder
{
public:
	Holder(int value);
	int get_value() const;
	void set_value(int value);

private:
	int value_;
};

void bind_example();