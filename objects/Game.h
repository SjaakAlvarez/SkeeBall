#pragma once

#include <raylib.h>
#include <chrono>
#include "../screens/GameOverScreen.h"
#include "../screens/StartScreen.h"
#include "../globals.h"



class Game {

protected:	
	std::array<int, 8> sensorsP1 = { { PIN_SENSOR1, PIN_SENSOR2,PIN_SENSOR3,PIN_SENSOR4,PIN_SENSOR5,PIN_SENSOR6,PIN_SENSOR7,PIN_SENSOR8 } };
	std::array<int, 8> sensorsP2 = { { PIN_SENSOR9, PIN_SENSOR10,PIN_SENSOR11,PIN_SENSOR12,PIN_SENSOR13,PIN_SENSOR14,PIN_SENSOR15,PIN_SENSOR16 } };
	std::array<int, 8> ledsP1 = { { 6,5,4,3,2,1,0,7 } };
	std::array<int, 8> scores = { { 10, 20,30,40,50,100,100,0 } };

private:	
	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();
	GameOverScreen* gameoverScreen;
	StartScreen* startScreen;	

public:
	enum class GameState { INIT, PLAYING, GAMEOVER };
	GameState gameState;
	bool showStart;
	int scoreP1 = 0;
	int scoreP2 = 0;
	std::string scoreUnit;
	std::string scoreUnitPlural;
	bool isTwoPlayer;

	void endGame();
	void initGame();
	void update();
	void draw();	
	Game();
	virtual ~Game();
	virtual void OnStart() {};
	virtual void OnQuit() {};
};