#pragma once

class counting_thing
{
public:
	counting_thing(); 
	counting_thing(const counting_thing & other);
	counting_thing(counting_thing && other) noexcept;
	counting_thing& operator=(const counting_thing& rhs);
	counting_thing& operator=(counting_thing&& rhs) noexcept;
	~counting_thing();

	static int total_instances();
	static int current_instances();

	int instance_number() const;

private:
	int instance_number_;
	static int total_instances_;
	static int current_instances_;
};
