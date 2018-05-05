#include "CppUnitTest.h"

#include <sstream>
#include <string>
#include "../Blink_game/PinConfig.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Blink_tests
{		
	TEST_CLASS(TestConfig)
	{
	public:
		
		TEST_METHOD(ParseConfig)
		{
			std::stringstream config;
			std::string config_text{ "{ \"p1_led\": 10, \"p1_button\": 11,\"p2_led\": 12, \"p2_button\": 13,\"state\": 14 }" };
			config << config_text;

			reaction_game::Pin_config cfg{ config };
			Assert::AreEqual(10, bcm_number(cfg.p1_led()));
			Assert::AreEqual(12, bcm_number(cfg.p2_led()));
			Assert::AreEqual(11, bcm_number(cfg.p1_button()));
			Assert::AreEqual(13, bcm_number(cfg.p2_button()));
			Assert::AreEqual(14, bcm_number(cfg.reaction_led()));
		}

		TEST_METHOD(ParseInvalidConfig)
		{
			std::stringstream config;
			std::string config_text{ "{ \"p1_led\": 10, \"p1_button\": 11,\"p3_led\": 12, \"p2_button\": 13,\"state\": 14 }" };
			config << config_text;

			Assert::ExpectException<std::exception>([&]() {reaction_game::Pin_config cfg{ config }; });
		}

	};
}