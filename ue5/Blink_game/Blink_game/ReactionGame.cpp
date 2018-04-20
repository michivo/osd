#include "ReactionGame.h"
#include "Enums.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <condition_variable>


namespace reaction_game {
	Reaction_game::Reaction_game(Player & p1, Player & p2, const Pin_config& cfg, int num_rounds) :
		p1_{ p1 },
		p2_{ p2 },
		num_rounds_{ num_rounds },
		led_output_{ cfg.reaction_led },
		p1_button_{ cfg.player1_button, pi_io::Pull_up_down::off, pi_io::Edge_type::rising, [&](pi_io::Pin)
		{
			std::unique_lock<std::mutex> lock(mutex_);
			p1.on_button_pressed();
			cv_.notify_one();
		} },
		p2_button_{ cfg.player2_button, pi_io::Pull_up_down::off, pi_io::Edge_type::rising, [&](pi_io::Pin)
		{
			std::unique_lock<std::mutex> lock(mutex_);
			p2.on_button_pressed();
			cv_.notify_one();
		} }
	{
	}

		Reaction_game::Game_result Reaction_game::play()
		{
			std::cout << "Starting game, get ready!" << std::endl;
			for (int i = 0; i < num_rounds_; i++)
			{
				if (!play_round())
				{
					std::cout << "Terminating game" << std::endl;
					return Game_result::aborted;
				}
				if (p1_.victory_count() > num_rounds_ / 2 || p2_.victory_count() > num_rounds_ / 2)
				{
					break;
				}
			}
			if (p1_.victory_count() > p2_.victory_count()) {
				return Game_result::p1_wins;
			}
			if (p2_.victory_count() > p1_.victory_count()) {
				return Game_result::p2_wins;
			}

			return Game_result::tie;
		}

		bool Reaction_game::play_round()
		{
			using namespace std::chrono;
			using namespace std::literals::chrono_literals;

			constexpr auto max_wait_time = 8s;
			constexpr auto min_wait_time = 3s;
			constexpr auto max_reaction_time = 3s;

			led_output_.set_state(pi_io::State::low);

			p1_.reset_button_time();
			p2_.reset_button_time();

			const auto wait_time = rand() % duration_cast<milliseconds>(max_wait_time - min_wait_time).count() +
				duration_cast<milliseconds>(min_wait_time).count();
			
			std::this_thread::sleep_for(duration<long long, std::milli>{ wait_time });
			const auto on_time = system_clock::now();
			led_output_.set_state(pi_io::State::high);

			std::unique_lock<std::mutex> lock(mutex_);
			cv_.wait_for(lock, max_reaction_time);

			led_output_.set_state(pi_io::State::low);
			if (!p1_.was_button_pressed() && !p2_.was_button_pressed())
			{
				return false;
			}

			check_result(on_time);
			return true;
		}

		void Reaction_game::check_result(const std::chrono::system_clock::time_point& on_time) const
		{
			if (p1_.was_button_pressed() && p1_.button_time() > on_time)
			{ // valid button press for p1_
				if (p2_.was_button_pressed() && p2_.button_time() > on_time)
				{ // valid button press for p2_
					if (p2_.button_time() < p1_.button_time())
					{
						std::cout << p2_.name() << " - you won!" << std::endl;
						p2_.add_victory();
						return;
					}
					if (p1_.button_time() < p2_.button_time())
					{
						std::cout << p1_.name() << " - you won!" << std::endl;
						p1_.add_victory();
						return;
					}

					std::cout << "This was a tie." << std::endl;
					return;
				}

				std::cout << p1_.name() << " - you won!" << std::endl;
				p1_.add_victory();
				return;
			}

			if (p2_.was_button_pressed() && p2_.button_time() > on_time)
			{ // valid button press for p2_
				std::cout << p2_.name() << " - you won!" << std::endl;
				p2_.add_victory();
				return;
			}

			std::cout << "This was a tie." << std::endl;
		}
}