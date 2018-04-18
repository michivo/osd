#include "Player.h"
#include <utility>

Player::Player(std::string name) :
	name_{std::move(name)}, win_count_{ 0 }
{
}

std::string Player::get_name() const
{
	return name_;
}

void Player::add_victory()
{
	win_count_++;
}

int Player::get_victory_count() const
{
	return win_count_;
}