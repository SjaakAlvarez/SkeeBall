#pragma once

#include <raylib.h>
#include <chrono>
#include "Drawable.h"

class Clock: public Drawable {

protected:

	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();
	int state=0;
	bool blinkState = true;
	bool ticking = true;
	SpriteFont digital;	

public:
	Vector2 pos;
	int width=5;
	int clockSize=100;
	int count = 10;
	void update();
	void draw();
	void stop();
	virtual ~Clock();
	Clock();
	void initialize();

};