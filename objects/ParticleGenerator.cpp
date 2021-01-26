#include "ParticleGenerator.h"
#include "Particle.h"
#include <chrono>
#include <string>
#include <algorithm>

void ParticleGenerator::update()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> now;
	now = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed_seconds = now - last;

	
	if (delay < 0) {
		start = true;
	}
	else {
		delay -= elapsed_seconds.count();
		last = now;
	}


	if (generated < maxParticles && start) {

		generate += elapsed_seconds.count()*particlesPerSecond;

		int count = ::floor(generate);
		if (count >= 1) generate = generate - count;
		for (int i = 0; i < count; i++) {

			Particle* p = new Particle();
			p->active = true;
			p->alpha = 1.0f;
			if (randomColor) {
				p->color = Color{ (unsigned char)GetRandomValue(0,255),(unsigned char)GetRandomValue(0,255),(unsigned char)GetRandomValue(0,255),255 };
			}
			else
			{
				p->color = color;
			}
				
			p->direction = Vector2{ (float)GetRandomValue(-speed,speed) / 10.0f,(float)GetRandomValue(-speed,speed) / 10.0f };
			p->gravity = true;
			p->position = position;
			p->rotation = GetRandomValue(-90, 90);
			if (maxAge != -1) {
				p->maxAge = maxAge;
			}
			else
			{
				p->maxAge = GetRandomValue(1, 3);
			}
			particles.push_back(p);
			generated++;

		}
		last = now;
	}

	for (int i = particles.size() - 1; i >= 0; i--)
	{
		particles[i]->rotation += 5;
		particles[i]->age += 0.016f;
		particles[i]->position.x += particles[i]->direction.x;
		particles[i]->position.y += particles[i]->direction.y;
		particles[i]->direction.x *= .99;
		particles[i]->direction.y += gravity;
		particles[i]->alpha = 1.0f - particles[i]->age / particles[i]->maxAge;

		if (particles[i]->age >= particles[i]->maxAge) {
			delete particles[i];
			particles.erase(particles.begin() + i);
		}

		

	}

	//std::remove_if(particles.begin(),particles.end(),[](Particle* x) {return x->age>x->maxAge; });

}

void ParticleGenerator::draw()
{
	//DrawText(std::to_string(particles.size()).c_str(), 150, 100, 20, WHITE);
	//DrawText(std::to_string(generate).c_str(), 150, 120, 20, WHITE);

	for (auto &p : particles)
	{
		if (useTexture) {
			Rectangle rect1{ 0,0,particleSize.x,particleSize.y };
			Rectangle rect2{ p->position.x, p->position.y,particleSize.x,particleSize.y };
			DrawTexturePro(texture, rect1, rect2, Vector2{ particleSize.x/2,particleSize.y/2 }, p->rotation, Fade(p->color, p->alpha));
		}
		else
		{
			DrawRectanglePro(Rectangle{ (p->position.x), (p->position.y), static_cast<float>(particleSize.x),  static_cast<float>(particleSize.y) }, Vector2{ (particleSize.x / 2), (particleSize.x / 2) }, p->rotation, Fade(p->color, p->alpha));
		}
	}
}

ParticleGenerator::~ParticleGenerator()
{
	TraceLog(LOG_INFO, "particlegenerator deleted");
}

ParticleGenerator::ParticleGenerator()
{
	delay = 0.0f;
	generated = 0;
	randomColor = false;
	generate = 0;
	start = false;
	useTexture = false;
	maxAge = -1;
	speed = 100;
}
