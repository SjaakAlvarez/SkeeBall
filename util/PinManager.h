#pragma once

#include <chrono>
#include <array>
#include <raylib.h>



static uint16_t pins[20];


class PinManager {

protected:
	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();

	int currentPinState[32] = { 0 };
	int previousPinState[32] = { 0 };	
	float debounce = 0.02;

	

	
	std::array<int, 20> keys = { {KEY_DOWN,KEY_UP,KEY_ENTER,KEY_BACKSPACE,
								  KEY_ONE,KEY_TWO,KEY_THREE,KEY_FOUR,KEY_FIVE,KEY_SIX,KEY_SEVEN,KEY_ZERO,
								  KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_Y,KEY_U,KEY_P
								} };
	std::array<int, 20> gpio = { { 18,14,15,23,
								   2,3,4,17,27,22,10,24,
								   9,11,0,5,6,13,19,26
							} };
public:
	bool isButtonPressed(int pin);
	void initialize();
	void update();
	void draw();	
	PinManager();
	static void updatePins(void);

};