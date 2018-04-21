#include "PinConfig.h"
#include <stdexcept>

namespace reaction_game
{

	Pin_config::Pin_config(pi_io::Pin p1_button, pi_io::Pull_up_down p1_pud, pi_io::Pin p1_led, 
		pi_io::Pin p2_button, pi_io::Pull_up_down p2_pud, pi_io::Pin p2_led, pi_io::Pin reaction_led) :
		p1_button_{p1_button}, p1_pud_{p1_pud}, p1_led_{p1_led},
		p2_button_{ p2_button }, p2_pud_{ p2_pud }, p2_led_{ p2_led }, reaction_led_{reaction_led}
	{
		if(p1_button_ == p1_led_ || p1_button_ == p2_button_ || p1_button_ == p2_led_ || p1_button_ == reaction_led_ ||
			p1_led_ == p2_button_ || p1_led_ == p2_led_ || p1_led_ == reaction_led_ || p2_button_ == p2_led_ ||
			p2_button_ == reaction_led_ || p2_led_ == reaction_led_)
		{
			throw std::invalid_argument("Duplicate use of pins is not allowed!");
		}
	}

	pi_io::Pin Pin_config::p1_button() const
	{
		return p1_button_;
	}

	pi_io::Pull_up_down Pin_config::p1_pud() const
	{
		return p1_pud_;
	}

	pi_io::Pin Pin_config::p1_led() const
	{
		return p1_led_;
	}

	pi_io::Pin Pin_config::p2_button() const
	{
		return p2_button_;
	}

	pi_io::Pull_up_down Pin_config::p2_pud() const
	{
		return p2_pud_;
	}

	pi_io::Pin Pin_config::p2_led() const
	{
		return p2_led_;
	}

	pi_io::Pin Pin_config::reaction_led() const
	{
		return reaction_led_;
	}

}
