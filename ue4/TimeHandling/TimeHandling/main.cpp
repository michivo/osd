#include <wiringPi.h>

#include <chrono>
#include <iostream>

constexpr int button = 3;

int64_t start_time_us = 0;
int button_count = 0;

void on_button();

int main(void)
{

	auto now = std::chrono::system_clock::now().time_since_epoch();
	start_time_us = std::chrono::duration_cast<std::chrono::microseconds>(now).count();
	wiringPiSetup();

	pinMode(button, INPUT);

	pullUpDnControl(button, PUD_OFF);

	wiringPiISR(button, INT_EDGE_RISING, &on_button);

	while (button_count < 3)
	{
		delay(500);
	}
	return 0;
}

void on_button() {
	auto now = std::chrono::system_clock::now().time_since_epoch();
	auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now).count() - start_time_us;

	std::cout << "Button was pressed after " << delta << "us" << std::endl;
	button_count++;
}