#pragma once

#include <vector>
#include <raylib.h>
#include "Particle.h"
#include <chrono>
#include <functional>
#include "Drawable.h"

class ParticleGenerator : public Drawable {

public:
	std::vector<Particle*> particles;
	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();

	void update();
	void draw();
	virtual ~ParticleGenerator();
	ParticleGenerator();
	void setTexture(Texture2D t) {
		texture = t;
		useTexture = true;
	}
	

	float particlesPerSecond;
	int maxParticles;
	int generated = 0;
	float generate=0;
	float delay=0.0f;
	bool start;
	bool useTexture = false;
	Texture2D texture;
	bool randomColor = false;
	Vector2 particleSize;
	float maxAge;
	int speed;

	Vector2 position;
	Color color;
	float gravity;
};