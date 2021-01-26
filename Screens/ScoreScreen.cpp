#include "ScoreScreen.h"

#include <raylib.h>
#include <chrono>
#include <string>
#include "ScreenManager.h"

#include <sstream> 
#include <iomanip>
#include "../globals.h"

#define WIDTH 6

ScoreScreen::ScoreScreen() {
	name = "score";
	counter = new Counter();
	counter->pos = Vector2{ 100,100 };
	counter->width = 6;
	counter->counterSize = 100;
	counter->animated = true;
	counter->count_increment = 1000;
	counter->initialize();
}



void ScoreScreen::draw() {
	
	counter->draw();
	DrawText("Press 1 to add 10 points, 2 to add 100 points or 3 to add 1000 points", 150, 600, 30, BEIGE);
}

void ScoreScreen::update() {	
	
	counter->update();

	if (IsKeyPressed(KEY_ONE)) {
		counter->count+=10;
	}
	if (IsKeyPressed(KEY_TWO)) {
		counter->count += 100;
	}
	if (IsKeyPressed(KEY_THREE)) {
		counter->count += 1000;
	}

	if (pinManager.isButtonPressed(PIN_BACK)) {
		ScreenManager::Instance().setActive("menumanager");
	}

}