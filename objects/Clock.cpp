#include "Clock.h"

#include <raylib.h>
#include <chrono>
#include <string>
#include <sstream> 
#include <iomanip>
#include <algorithm>
#include "../globals.h"


Clock::Clock() {
	
}

void Clock::initialize()
{	
	//int characters[27];
	//for (unsigned int i = 0; i < 27; i++) characters[i] = 32 + i;	
	digital = LoadFontEx("resources/digital-7 (mono).ttf", clockSize, 0, 0);// 27, characters);
}

void Clock::update()
{

	std::chrono::time_point<std::chrono::high_resolution_clock> now;
	now = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed_seconds = now - last;

	if (state == 0 && ticking)
	{
		if (elapsed_seconds.count() > 1 && count > 0)
		{
			count--;
			last = now;

			if (count == 0) state = 1;
		}
	}
	else if (state == 1)
	{
		if (elapsed_seconds.count() > 0.75f)
		{
			blinkState = !blinkState;
			last = now;
		}
	}

}

void Clock::draw()
{
	Vector2 correction;

	float scale = clockSize/100.0f;

	correction.x = pos.x;
	correction.y = pos.y;// +(130 * scale);
	//DrawRectangle(pos.x, pos.y, width * 83 , 140, GREEN);
	DrawRectangle(pos.x, pos.y, width * 83*scale, 140*scale, BLACK);

	

	std::stringstream clock;
	clock << std::setfill('0') << std::setw(2) << floor(count / 60) << ":" << std::setfill('0') << std::setw(2) << count % 60;

	DrawTextEx(digital, "88:88", correction, clockSize, 0, CLITERAL(Color){ 32,0,0,255 });
	if (blinkState) DrawTextEx(digital, clock.str().c_str(), correction, clockSize, 0, CLITERAL(Color){ 255,0,0,255 });
	

}

void Clock::stop()
{
	ticking = false;
}


Clock::~Clock()
{
	UnloadFont(digital);
}
