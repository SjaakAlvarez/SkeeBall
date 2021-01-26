#pragma once
#include "Screen.h"
#include <raylib.h>
#include <array>
#include "../objects/Clock.h"
#include "../objects/Game.h"
#include "../objects/Counter.h"





class TimeBomb : public Screen, public Game {

protected:

	enum class State { PLAYING, STARTLEVEL, GAMEOVER };

	std::vector<std::shared_ptr<ParticleGenerator>> generators;
	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();
	Texture2D texturebk;
	Texture2D textureLed1;
	Texture2D textureLed2;
	Texture2D textureLed3;
	std::array<int, 8> ballmap{ { 0,1,2,3,4,5,5,6 } };

	std::array<int, 8> disarmValues{ { 10,20,30,40,50,100 } };

	Clock* clock;
	int t;
	bool t1, t2, t3;
	int blinkspeed = 1;
	std::vector<int> disarmCode;
	int activeCode = 0;
	int maxCode;
	int level;
	State state;
	
public:
	void createNewSequence();
	void startNewLevel();
	void update();
	void draw();
	TimeBomb();
	virtual ~TimeBomb();
	void OnStart();
	void OnQuit();
};