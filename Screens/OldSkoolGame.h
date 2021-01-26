#pragma once

#include "Screen.h"
#include <raylib.h>
#include "../objects/Counter.h"
#include "../objects/Game.h"
#include <chrono>

class OldSkoolGame : public Screen,public Game {

protected:
	Texture2D texturebk;
	Texture2D texFreeGame;
	Texture2D texGameOver;
	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();
	bool showFreeGame;
	bool showGameOver;

public:
	int score=0;
	int balls=9;
	

	Counter* scorecounter;
	Counter* ballcounter;
	
	void OnQuit();
	void draw();
	void update();
	OldSkoolGame();
	virtual ~OldSkoolGame();

};