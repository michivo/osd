#pragma once

#include <string>

class Player
{
public:
	Player(std::string name);

	std::string get_name() const;

	void add_victory();

	int get_victory_count() const;

private:
	std::string name_;
	int win_count_;
};

