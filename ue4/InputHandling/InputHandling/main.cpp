#include <wiringPi.h>

#include <iostream>

constexpr int button_1 = 3;
constexpr int button_2 = 4;

int press_count = 0;

void on_button_1();
void on_button_2();

int main(void)
{
	wiringPiSetup();

	pinMode(button_1, INPUT);
	pinMode(button_2, INPUT);

	pullUpDnControl(button_1, PUD_OFF);
	pullUpDnControl(button_2, PUD_OFF);

	wiringPiISR(button_1, INT_EDGE_RISING, &on_button_1);
	wiringPiISR(button_2, INT_EDGE_RISING, &on_button_2);

	while (press_count < 3)
	{
		delay(500);
	}
	return 0;
}

void on_button_1() {
	std::cout << "Button 1 was pressed!" << std::endl;
	press_count++;
}

void on_button_2() {
	std::cout << "Button 2 was pressed!" << std::endl;
	press_count--;
}