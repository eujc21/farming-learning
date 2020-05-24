#include <iostream>
#include <wiringPi.h>
#include <csignal>

using namespace std;

// global flag used to exit from the main loop
bool RUNNING = true;

// Blink LED
void blink_led(int led, int time) {
	digitalWrite(led, HIGH);
	delay(time);
	digitalWrite(led, LOW);
	delay(time);
}

// Callback handler if CTRL-C signal is detected
void my_handler(int s) {
	cout << "Detected CTRL-C signal no. " << s << endl;
	RUNNING = false;
}

int main(void) {
	// Register a callback function to be called if the user processes CTRL-C
	signal(SIGINT, my_handler);

	// Initialize wiringPi and allow the use of BCM pin numbering
	wiringPiSetup();

	cout << "Controlling the GPI pins with wiringPi" << endl;

	int red = 17, yellow = 22, green = 6;

	pinMode(red, OUTPUT);
	pinMode(yellow, OUTPUT);
	pinMode(green, OUTPUT);

	int time = 1000;

	while(RUNNING) {
		blink_led(red, time);
		blink_led(yellow, time);
		blink_led(green, time);
	}

	cout << "Program ended ..." << endl;
}

