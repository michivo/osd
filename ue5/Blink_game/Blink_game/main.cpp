#include "Pin.h"

#include "Player.h"
#include "PinConfig.h"
#include "ReactionGame.h"

#include <iostream>
#include <fstream>

//-------------------------------------------------------------------------------------------------
// MAIN
//-------------------------------------------------------------------------------------------------
int main(void)
{
	using namespace pi_io;

	const auto p1 = reaction_game::create_player(1);
	const auto p2 = reaction_game::create_player(2);

	std::cout << "How many rounds do you want to play? ";
	int count = 0;

	const auto max_num_rounds = 100;
	const auto min_num_rounds = 1;

	if (!(std::cin >> count) || count < min_num_rounds || count > max_num_rounds)
	{
		std::cout << "Invalid number of rounds, enter a number between "
			<< min_num_rounds << " and " << max_num_rounds << std::endl;
		return 0;
	}

	std::ifstream pin_file{ "pins.json" };
	const reaction_game::Pin_config cfg{ pin_file };

	reaction_game::Reaction_game game{ p1, p2, cfg, count };
	game.play();

	return 0;
}
