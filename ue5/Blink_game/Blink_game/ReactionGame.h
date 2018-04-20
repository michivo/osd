#pragma once
#include "Player.h"
#include "PiDigitalOutput.h"
#include "PinConfig.h"
#include "PiDigitalInput.h"

#include <mutex>
#include <condition_variable>

namespace reaction_game {

	class Reaction_game
	{
	public:
		Reaction_game(Player& p1, Player& p2, const Pin_config& cfg, int num_rounds);

		enum class Game_result { p1_wins, p2_wins, tie, aborted };

		Game_result play();

	private:
		Player & p1_;
		Player& p2_;
		int num_rounds_;
		pi_io::Pi_digital_output led_output_;
		pi_io::Pi_digital_input p1_button_;
		pi_io::Pi_digital_input p2_button_;
		std::condition_variable cv_;
		std::mutex mutex_;

		bool play_round();
		void check_result(const std::chrono::system_clock::time_point & on_time) const;
	};
}
