#include "ThreeTen.h"
#include <raylib.h>
#include "ScreenManager.h"
#include "../objects/Counter.h"
#include "../globals.h"

ThreeTen::ThreeTen() {

	texturebk = LoadTexture("resources/threeten/background.png");
	isTwoPlayer = false;
	scoreUnit = "throw";
	scoreUnitPlural = "throws";

	scorecounter = new Counter();
	scorecounter->pos = Vector2{ 150,85 };
	scorecounter->width = 3;
	scorecounter->counterSize = 150;
	scorecounter->animated = false;
	scorecounter->count = 310;
	scorecounter->initialize();

	ballcounter = new Counter();
	ballcounter->pos = Vector2{ 800,125 };
	ballcounter->width = 2;
	ballcounter->count = 0;
	ballcounter->counterSize = 90;
	ballcounter->animated = false;
	ballcounter->initialize();

	items.push_back(scorecounter);
	items.push_back(ballcounter);

	initGame();
}

ThreeTen::~ThreeTen()
{
	delete ballcounter;
	delete scorecounter;
	UnloadTexture(texturebk);
}

void ThreeTen::update() {
	Screen::update();

	if (gameState == GameState::PLAYING) {
		
		for (unsigned int i = 0; i < 8; i++) {
			if (pinManager.isButtonPressed(sensorsP1[i])) {
				if (scorecounter->count >= scores[i]) {
					scorecounter->count -= scores[i];
				}
				ballcounter->count++;
			}
		}

		if (scorecounter->count == 0) {
			scoreP1 = ballcounter->count;
			endGame();
		}
	}

	Game::update();
}

void ThreeTen::OnQuit() {
	ScreenManager::Instance().setActive("menumanager");
	ScreenManager::Instance().removeScreen("threeten");	
	delete this;
}

void ThreeTen::draw() {
	DrawTexture(texturebk, 0, 0, WHITE);
	Screen::draw();
}