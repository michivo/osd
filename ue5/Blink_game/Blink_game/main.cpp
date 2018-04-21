#include "Pin.h"

#include <iostream>
#include "Player.h"
#include "PinConfig.h"
#include "ReactionGame.h"

Player create_player(int player_number)
{
	std::string player_name;
	std::cout << "Player " << player_number << ", enter your name: ";
	std::cin >> player_name;
	return Player{ player_name };
}

//-------------------------------------------------------------------------------------------------
// MAIN
//-------------------------------------------------------------------------------------------------
int main(void)
{
	using namespace pi_io;

	auto p1 = create_player(1);
	auto p2 = create_player(2);

	std::cout << "How many rounds do you want to play? ";
	int count;
	if(!(std::cin >> count) || count < 1 || count > 100)
	{
		std::cout << "Invalid number of rounds, enter a number between 1 and 100" << std::endl;
		return 0;
	}
	
	const reaction_game::Pin_config cfg{ Pin::bcm_2 , Pull_up_down::off, Pin::bcm_17,
		Pin::bcm_27, Pull_up_down::off, Pin::bcm_10, Pin::bcm_22};

	reaction_game::Reaction_game game{ p1, p2, cfg, count };
	const auto result = game.play();

	if (result == reaction_game::Reaction_game::Game_result::p1_wins) {
		std::cout << p1.name() << " is the overall winner!" << std::endl;
	}
	else if (result == reaction_game::Reaction_game::Game_result::p2_wins) {
		std::cout << p2.name() << " is the overall winner!" << std::endl;
	}
	else if (result == reaction_game::Reaction_game::Game_result::tie){
		std::cout << "The result is an overall tie, you are both champs!" << std::endl;
	}
	else {
		std::cout << "Game aborted due to inactivity" << std::endl;
	}

	return 0;
}
