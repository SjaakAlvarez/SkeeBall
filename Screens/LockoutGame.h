#pragma once
#include "Screen.h"
#include <raylib.h>
#include <array>
#include "../objects/Clock.h"
#include "../objects/Game.h"
#include "../objects/Counter.h"


class LockoutGame : public Screen, public Game {

protected:
	Texture2D texturebk;
	Texture2D textureBall;
	Texture2D textureLock;
	std::array<int, 6> balls;
	Clock* clock;
	std::array<int, 7> ballmap{ {5,4,3,2,1,0,0} };
	Counter* counterP1;
	Counter* counterP2;
	bool allLocked();

public:
	void OnQuit();
	void update();
	void draw();
	LockoutGame();
	virtual ~LockoutGame();
};