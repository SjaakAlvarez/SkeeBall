#pragma once

#include <chrono>
#include <functional>
#include <raylib.h>
#include "Drawable.h"

class Sprite : public Drawable {

protected:
	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();
	Texture2D tex;
	int frameCount;
	int currentFrame;
	

public:
	Vector2 pos;
	Sprite();
	virtual ~Sprite();
	void start();
	void stop();
	void update();
	void draw();

};