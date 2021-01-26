#pragma once

#include "Screen.h"
#include <chrono>
#include <raylib.h>
#include <memory>
#include <array>

class StartScreen :public Screen {

private:	
	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();

	SpriteFont rocket;
	Texture2D texturebk;
	int t;
	int displayText;
	std::array<std::string, 5> texts = { {"ready","set","go","",""} };
	

public:
	virtual void update();
	virtual void draw();
	StartScreen();
	virtual ~StartScreen();
	

};