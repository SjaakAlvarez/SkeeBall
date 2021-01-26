#pragma once

#include "Screen.h"
#include <chrono>
#include <raylib.h>
#include "../objects/ParticleGenerator.h"
#include <memory>

class GameOverScreen :public Screen {

private:
	std::vector<std::shared_ptr<ParticleGenerator>> generators;
	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();
	
	SpriteFont rocket;
	Texture2D texturebk;	
	Texture2D texturebox;
	int scoreP1 = 0;
	int scoreP2 = 0;
	std::string scoreUnit;
	std::string scoreUnitPlural;
	bool isTwoPlayer;
	int state;
	int t;

public:	
	virtual void update();
	virtual void draw();
	GameOverScreen();
	virtual ~GameOverScreen();
	void setInfo(int s1, int s2, std::string unit, std::string unitPlural, bool is2p);
	


};