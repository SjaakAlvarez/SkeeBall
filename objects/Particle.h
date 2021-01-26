#pragma once

#include <raylib.h>

class Particle {

public:
	Vector2 position;
	Vector2 direction;
	Color color;
	float rotation;
	float alpha;
	bool active;
	bool gravity;
	float maxAge;
	float age = 0;
	

	Particle();
	virtual ~Particle();
};