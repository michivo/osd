#pragma once
#include "Pin.h"
#include "Enums.h"

namespace reaction_game
{
	struct Pin_config
	{
		pi_io::Pin player1_button;
		pi_io::Pull_up_down player1_pud;
		pi_io::Pin player2_button;
		pi_io::Pull_up_down player2_pud;
		pi_io::Pin player1_led;
		pi_io::Pin player2_led;
		pi_io::Pin reaction_led;
	};
}
