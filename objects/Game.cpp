#include "Game.h"
#include "../globals.h"
#include <chrono>
#include "../screens/ScreenManager.h"


void Game::endGame()
{	
	gameState = GameState::GAMEOVER;
	last=std::chrono::high_resolution_clock::now();
}


void Game::initGame()
{		
	scoreP1 = 0;
	scoreP2 = 0;
	gameState = GameState::INIT;		
	last = std::chrono::high_resolution_clock::now();
}

void Game::update()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> now;
	now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - last;

	switch (gameState) {
	case GameState::INIT:
		if (!showStart) {						
			showStart = true;
			ScreenManager::Instance().addScreen(startScreen, "start");
		}
		if (elapsed_seconds.count() > 4.5f)
		{
			if (startScreen != nullptr) {
				ScreenManager::Instance().removeScreen("start");
				delete startScreen;
			}
			gameState = GameState::PLAYING;			
			OnStart();
		}
		break;
	case GameState::PLAYING:
		break;
	case GameState::GAMEOVER:
		if (elapsed_seconds.count() > 1 && gameState!=GameState::PLAYING && gameoverScreen == nullptr) {
			gameoverScreen = new GameOverScreen();
			gameoverScreen->setInfo(scoreP1, scoreP2, scoreUnit, scoreUnitPlural, isTwoPlayer);
			ScreenManager::Instance().addScreen(gameoverScreen, "gameover");
		}

		if ((pinManager.isButtonPressed(PIN_BACK) || pinManager.isButtonPressed(PIN_ENTER))) {
			if (gameoverScreen != nullptr) {
				ScreenManager::Instance().removeScreen("gameover");
				delete gameoverScreen;
			}
			OnQuit();			
		}
		break;
	}
}

void Game::draw()
{
}

Game::Game()
{		
	gameoverScreen = nullptr;
	gameState = GameState::INIT;
	startScreen = new StartScreen();
	showStart = false;
}

Game::~Game()
{
}
