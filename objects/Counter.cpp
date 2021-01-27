#include "Counter.h"

#include <raylib.h>
#include <chrono>
#include <string>
#include <sstream> 
#include <iomanip>
#include <algorithm>
#include "../globals.h"


Counter::Counter() {
	
}

void Counter::update()
{
	if (animated)
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> now;
		now = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> elapsed_seconds = now - last;

		int increment = std::max(2.0, count_increment*elapsed_seconds.count());

		last = now;

		if (count_displayed < count) {
			count_displayed += increment;
			if (count_displayed > count) count_displayed = count;
		}
		
		
	}
	else {
		count_displayed = count;
	}
	if (count_displayed < 0) count_displayed = 0;
}

void Counter::draw()
{
	Vector2 correction;

	float scale = counterSize / 100.0f;

	correction.x = pos.x;
	correction.y = pos.y;// +(130 * scale);
	DrawRectangle(pos.x, pos.y, width * 83*scale, 140*scale, BLACK);

	std::stringstream ss;
	ss << std::setfill('8') << std::setw(width) << 8;

	std::stringstream sc;
	sc << std::setfill(' ') << std::setw(width) << count_displayed;

	DrawTextEx(digital, ss.str().c_str(), correction, counterSize, 0, CLITERAL(Color){ 32,0,0,255 });
	DrawTextEx(digital, sc.str().c_str(), correction, counterSize, 0, CLITERAL(Color){ 255,0,0,255 });
	
}

Counter::~Counter()
{
	UnloadFont(digital);
}

void Counter::initialize()
{
	//int characters[26];
	//for (unsigned int i = 0; i < 26; i++) characters[i] = 32 + i;
	digital = LoadFontEx("resources/digital-7 (mono).ttf", counterSize, 0, 0);// 26, characters);
}