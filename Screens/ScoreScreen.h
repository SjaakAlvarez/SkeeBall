#pragma once

#include <chrono>
#include "Screen.h"
#include <raylib.h>
#include "../objects/Counter.h"

class ScoreScreen : public Screen{

private:	
	Counter* counter;
public:
	virtual void update();
	virtual void draw();
	ScoreScreen();
	
};