#include "Sprite.h"

Sprite::Sprite()
{
	tex= LoadTexture("resources/slot/anim.png");
	frameCount = 15;
	currentFrame = GetRandomValue(0, 14);
	pos = Vector2{ 100,100 };
}

Sprite::~Sprite()
{
}

void Sprite::start()
{
}

void Sprite::stop()
{
}

void Sprite::update()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> now;
	now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - last;

	if (elapsed_seconds.count() > 0.03f) {
		currentFrame++;
		if (currentFrame == frameCount) currentFrame = 0;
		last = now;
	}
}

void Sprite::draw()
{
	Rectangle rect{ 0,currentFrame * 200,200,200 };
	DrawTextureRec(tex, rect, pos, WHITE);
}
