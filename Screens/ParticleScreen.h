#pragma once

#include "Screen.h"
#include <chrono>
#include <raylib.h>
#include "../objects/ParticleGenerator.h"
#include <memory>

#define MAX_GEN 10

class ParticleScreen :public Screen {

private:

	std::vector<std::shared_ptr<ParticleGenerator>> generators;
	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();
	int count=0;

public:
	virtual void update();
	virtual void draw();
	ParticleScreen();
	virtual ~ParticleScreen();


};