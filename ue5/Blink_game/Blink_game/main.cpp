#include "Pin.h"

#include <iostream>
#include "Player.h"
#include "PinConfig.h"
#include "ReactionGame.h"

using namespace pi_io;

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
	Player p1 = create_player(1);
	Player p2 = create_player(2);

	std::cout << "How many rounds do you want to play? ";
	int count;
	std::cin >> count;
	
	reaction_game::Pin_config cfg{};
	cfg.reaction_led = Pin::bcm_2;
	cfg.player1_button = Pin::bcm_22;
	cfg.player2_button = Pin::bcm_23;

	reaction_game::Reaction_game game{ p1, p2, cfg, count };
	auto result = game.play();

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
