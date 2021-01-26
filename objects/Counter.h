#pragma once

#include <raylib.h>
#include <chrono>
#include "Drawable.h"

class Counter : public Drawable {

protected:
	
	int count_displayed = 0;	
	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now(); 
	SpriteFont digital;
	
public:
	Vector2 pos;
	int width;
	int count = 0;
	int count_increment = 10;
	int counterSize;
	bool animated = false;;
	void update();
	void draw();
	virtual ~Counter();
	void initialize();
	Counter();

};