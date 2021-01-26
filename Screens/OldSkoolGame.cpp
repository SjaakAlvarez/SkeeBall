#include "OldSkoolGame.h"
#include <raylib.h>
#include "ScreenManager.h"
#include "../objects/Counter.h"
#include "../globals.h"
#include "../led/LedManager.h"

OldSkoolGame::OldSkoolGame() {

	texturebk = LoadTexture("resources/oldskool/background.png");
	texFreeGame = LoadTexture("resources/oldskool/freegame.png");
	texGameOver = LoadTexture("resources/oldskool/gameover.png");

	scorecounter = new Counter();	
	scorecounter->pos = Vector2{ 455,245 };
	scorecounter->width = 3;
	scorecounter->counterSize = 150;
	scorecounter->animated = true;
	scorecounter->count_increment = 500;
	scorecounter->initialize();

	ballcounter = new Counter();
	ballcounter->pos = Vector2{ 604,522 };
	ballcounter->width = 1;
	ballcounter->count = balls;
	ballcounter->counterSize = 90;
	ballcounter->animated = false;
	ballcounter->initialize();

	items.push_back(scorecounter);
	items.push_back(ballcounter);

	isTwoPlayer = false;
	showFreeGame = false;
	showGameOver = false;
	scoreUnit = "point";
	scoreUnitPlural = "points";
	initGame();
}

OldSkoolGame::~OldSkoolGame()
{
	delete ballcounter;
	delete scorecounter;
	UnloadTexture(texGameOver);
	UnloadTexture(texFreeGame);
	UnloadTexture(texturebk);
}

void OldSkoolGame::update() {
	Screen::update();

	if (gameState==GameState::PLAYING) {
		std::chrono::time_point<std::chrono::high_resolution_clock> now;
		now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed_seconds = now - last;

		if (elapsed_seconds.count() > 0.9) {
			showFreeGame = !showFreeGame;			
			last = now;
		}

		for (unsigned int i = 0; i < 8; i++) {
			if (pinManager.isButtonPressed(sensorsP1[i]) && ballcounter->count>0) {
				scorecounter->count += scores[i];
				for (unsigned int j = 0; j < 8; j++) {
					LedManager::Instance().setColor(ledsP1[j], BLACK);
				}
				LedManager::Instance().setColor(ledsP1[i], WHITE);
				ballcounter->count -= 1;
			}
			
		}

		if (ballcounter->count <= 0) {
			showGameOver = true;
			scoreP1 = scorecounter->count;
			endGame();
		}
	}

	Game::update();	
}

void OldSkoolGame::OnQuit() {
	ScreenManager::Instance().setActive("menumanager");
	ScreenManager::Instance().removeScreen("oldskool");	
	delete this;
}

void OldSkoolGame::draw() {

	DrawTexture(texturebk, 0, 0, WHITE);
	if (showFreeGame) DrawTexture(texFreeGame, 0, 0, WHITE);
	if (showGameOver) DrawTexture(texGameOver, 1280 - 400, 0, WHITE);
	Screen::draw();
	
}