#include "LockoutGame.h"
#include "../globals.h"
#include "ScreenManager.h"

bool LockoutGame::allLocked()
{	
	for (unsigned int i = 0; i < 6; i++) {
		if (balls[i] != 3 && balls[i] != -3)
			return false;
	}
	return true;
}

void LockoutGame::update()
{
	if (gameState == GameState::PLAYING)
	{
		for (unsigned int i = 0; i < 7; i++) {
			
			if (pinManager.isButtonPressed(sensorsP1[i])) {
				if (balls[ballmap[i]] > -3 && balls[ballmap[i]]!=3)
				{
					balls[ballmap[i]]--;
					scoreP1 += scores[i];
				}			
			}

			if (pinManager.isButtonPressed(sensorsP2[i])) {
				if (balls[ballmap[i]] <3 && balls[ballmap[i]] != -3)
				{
					balls[ballmap[i]]++;
					scoreP2 += scores[i];
				}
			}

			counterP1->count = scoreP1;
			counterP2->count = scoreP2;
		}

		clock->update();
		

		if (clock->count == 0 || allLocked()) {
			for (unsigned int i = 0; i < 6; i++) {
				balls[i] = 3;
			}			
			endGame();
		}
	}

	counterP1->update();
	counterP2->update();

	Game::update();
}

void LockoutGame::OnQuit() {	
	ScreenManager::Instance().setActive("menumanager");
	ScreenManager::Instance().removeScreen("lockout");
	delete this;
}

void LockoutGame::draw()
{
	DrawTexture(texturebk, 0, 0, WHITE);
	for (unsigned int i = 0; i < 6; i++) {
		if (balls[i] == 3 || balls[i] == -3) {
			DrawTexture(textureLock, 299, 156 + i * 80, WHITE);
		}
		else
		{
			DrawTexture(textureBall, 600 + balls[i] * 90, 184 + i * 80, WHITE);
		}
	}
	clock->draw();
	counterP1->draw();
	counterP2->draw();
}

LockoutGame::LockoutGame()
{
	texturebk = LoadTexture("resources/lockout/background.png");
	textureBall = LoadTexture("resources/lockout/ball.png");
	textureLock = LoadTexture("resources/lockout/lock.png");

	clock = new Clock();
	clock->pos = Vector2{ 512,75 };
	clock->count = 120;
	clock->clockSize = 60;
	clock->initialize();

	counterP1 = new Counter();
	counterP2 = new Counter();

	counterP1->pos = Vector2{ 33,75 };
	counterP1->width = 5;
	counterP1->counterSize = 60;
	counterP1->animated = true;
	counterP1->count_increment = 500;
	counterP1->initialize();

	counterP2->pos = Vector2{ 997,75 };
	counterP2->width = 5;
	counterP2->counterSize = 60;
	counterP2->animated = true;
	counterP2->count_increment = 500;
	counterP2->initialize();

	for (unsigned int i = 0; i < 6; i++) {
		balls[i] = 0;
	}
	isTwoPlayer = true;
	scoreUnit = "point";
	scoreUnitPlural = "points";
	initGame();
}

LockoutGame::~LockoutGame()
{
	delete counterP2;
	delete counterP1;
	delete clock;
	UnloadTexture(textureLock);
	UnloadTexture(textureBall);
	UnloadTexture(texturebk);
}
