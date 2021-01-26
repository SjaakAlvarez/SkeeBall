#include "StartScreen.h"
#include "ScreenManager.h"
#include <easings.h>
#include "../globals.h"

void StartScreen::update()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> now;
	now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - last;
	t++;
	if (t == 90)
	{
		t = 0;
		displayText++;
	}
	
}


void StartScreen::draw()
{
	int textSize = 120;	
	int x = 0;

	DrawRectangle(0, 260, 1280, 200, Color{ 0,0,0,200 });
	if (t < 30) {
		x = EaseExpoOut(t, 0, 640, 30);
	}
	else if (t < 60) {
		x = 640;
	}
	else if (t < 90) {
		x = EaseBackIn(t-60, 640, 1280, 30);		
	}
	//DrawTextExCentered(rocket, texts[displayText].c_str(), Vector2{ (float)x + 2,362 }, textSize, 0, BLACK);
	DrawTextExCentered(rocket, texts[displayText].c_str(), Vector2{ (float)x,240 }, textSize, 0, RAYWHITE);
	
}

StartScreen::StartScreen()
{
	name = "start";
	//rocket = LoadSpriteFontEx("resources/start/test.png", 100, 0, 0);
	rocket = LoadFont("resources/start/test.fnt");
//	texturebk = LoadTexture("resources/start/background.png");
	isOverlay = true;
	t = 0;
	displayText = 0;
}

StartScreen::~StartScreen()
{
	UnloadFont(rocket);
//	UnloadTexture(texturebk);
}

