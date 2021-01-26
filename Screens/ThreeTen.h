#pragma once

#include "Screen.h"
#include <raylib.h>
#include "../objects/Counter.h"
#include "../objects/Game.h"
#include <chrono>

class ThreeTen : public Screen,public Game {

protected:
	Texture2D texturebk;	

public:
	int score=310;
	int balls=0;
	Counter* scorecounter;
	Counter* ballcounter;
	
	void OnQuit();
	void draw();
	void update();
	ThreeTen();
	virtual ~ThreeTen();

};