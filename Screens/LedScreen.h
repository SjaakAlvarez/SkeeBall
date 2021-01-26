#pragma once

#include <chrono>
#include "Screen.h"
#include <raylib.h>

class LedScreen : public Screen {

private:
	int pos = 0;
	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();

public:
	virtual void update();
	virtual void draw();
	LedScreen();
	virtual ~LedScreen();

	Color Wheel(int);
};