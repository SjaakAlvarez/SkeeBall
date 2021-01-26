#include "LedScreen.h"

#include <raylib.h>
#include <chrono>
#include <string>
#include "ScreenManager.h"
#include "../led/LedManager.h"
#include "../globals.h"


LedScreen::LedScreen() {
	name = "led";
}

LedScreen::~LedScreen() {
	
}

void LedScreen::draw() {


}

void LedScreen::update() {
	std::chrono::time_point<std::chrono::high_resolution_clock> now;
	now = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed_seconds = now - last;



	if (elapsed_seconds.count() > 0.01f) {
		last = now;
		pos+=2;

		for (int i = 0; i < 8; i++){		
			Color color = Wheel((pos+(i*8)) % 255);
			LedManager* ledManager = &LedManager::Instance();
			ledManager->setColor(i, color);
		}
	}



	if (pinManager.isButtonPressed(PIN_BACK)) {
		ScreenManager::Instance().setActive("menumanager");
	}

}

Color LedScreen::Wheel(int WheelPos) {
	//WheelPos = 255 - WheelPos;
	Color c;

	if (WheelPos < 85) {

		c.r = 255 - WheelPos * 3;
		c.g = 0;
		c.b = WheelPos * 3;
		c.a = 255;
		return c;
	}
	else if (WheelPos < 170) {
		WheelPos -= 85;
		c.r = 0;
		c.g = WheelPos * 3;
		c.b = 255 - WheelPos * 3;
		c.a = 255;
		return c;
	}
	else {
		WheelPos -= 170;
		c.r = WheelPos * 3;
		c.g = 255 - WheelPos * 3;
		c.b = 0;
		c.a = 255;
	}

	return c;
}