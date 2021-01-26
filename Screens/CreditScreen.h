#pragma once
#include "Screen.h"
#include "../objects/ParticleGenerator.h"
#include <raylib.h>
#include <array>
#include <chrono>
#include <memory>
#include "../globals.h"
#include "../screens/ScreenManager.h"
#include <easings.h>
#include "../objects/Sprite.h"

class MovingText {
public:
	Vector2 start;
	Vector2 end;
	Vector2 pos;
	float delay;
	std::string text;
	int t;	

};

class CreditScreen : public Screen {

protected:

	Texture2D texturebk;
	Texture2D texOverlay;
	Texture2D texture;
	Sprite sprite[3];
	
	std::vector<std::shared_ptr<ParticleGenerator>> generators;
	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();

	SpriteFont rocket;
	std::array<MovingText, 5> info;
	Texture2D textureStar;

public:

	void update();
	void draw();
	CreditScreen();
	virtual ~CreditScreen();
};