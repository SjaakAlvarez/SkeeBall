#pragma once
#include "Screen.h"
#include <raylib.h>
#include <array>
#include "../objects/Clock.h"
#include "../objects/Game.h"
#include "../objects/Counter.h"



class Mole {
public:
	unsigned int frame;
	Vector2 pos;
};

class MoleGame : public Screen, public Game {

protected:
	std::vector<std::shared_ptr<ParticleGenerator>> generators;
	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();
	Texture2D texturebk;
	Texture2D textureMole;
	Texture2D texturePoints;
	Texture2D textureStar;
	std::array<Mole, 6> moles;
	std::array<int, 8> ballmap{ { 0,1,2,3,4,5,5,6 } };
	Clock* clock;
	Counter* counterP1;
	Counter* counterBalls;	
	void generateBoom(Vector2 pos);
	void newMole();
	int activeMole;	

public:
	void update();
	void draw();
	MoleGame();
	virtual ~MoleGame();
	void OnStart();
	void OnQuit();
};