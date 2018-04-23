#include "Pin.h"

#include "Player.h"
#include "PinConfig.h"
#include "ReactionGame.h"

#include <iostream>

reaction_game::Pin_config get_pin_config(const reaction_game::Pin_config& cfg)
{
	const auto p1_button = pi_io::Pin::bcm_2;
	const auto p1_led = pi_io::Pin::bcm_17;
	const auto p2_button = pi_io::Pin::bcm_27;
	const auto p2_led = pi_io::Pin::bcm_10;
	const auto reaction_led = pi_io::Pin::bcm_22;

	return reaction_game::Pin_config{ p1_button , pi_io::Pull_up_down::off, p1_led,
		p2_button, pi_io::Pull_up_down::off, p2_led, reaction_led};
}

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

	if(!(std::cin >> count) || count < min_num_rounds || count > max_num_rounds)
	{
		std::cout << "Invalid number of rounds, enter a number between " 
		          << min_num_rounds << " and " << max_num_rounds << std::endl;
		return 0;
	}

	auto cfg = get_pin_config(cfg);

	reaction_game::Reaction_game game{ p1, p2, cfg, count };
	game.play();

	return 0;
}
