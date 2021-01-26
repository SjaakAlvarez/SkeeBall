#include "ParticleScreen.h"
#include "ScreenManager.h"
#include "../globals.h"
void ParticleScreen::update()
{	
	std::chrono::time_point<std::chrono::high_resolution_clock> now;
	now = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed_seconds = now - last;

	if (elapsed_seconds.count() > 1 && count<MAX_GEN) {

		last = now;

		count++;	
		std::shared_ptr<ParticleGenerator> gen = std::make_shared<ParticleGenerator>();		
		gen->particlesPerSecond = 1000;
		gen->maxParticles = 100;
		gen->gravity = 0.1f;
		gen->color = WHITE;
		gen->particleSize = Vector2{ 10, 10 };
		gen->position = Vector2{ (float)GetRandomValue(100,1180),(float)GetRandomValue(100,620) };
		

		generators.push_back(gen);
		
	}

	for (unsigned int i = 0; i < generators.size(); i++)
	{
		generators[i]->update();
	}

	if (pinManager.isButtonPressed(PIN_BACK)) {
		ScreenManager::Instance().setActive("menumanager");
	}
}


void ParticleScreen::draw()
{
	for (unsigned int i = 0; i < generators.size(); i++)
	{
		generators[i]->draw();
	}
}

ParticleScreen::ParticleScreen()
{
	name = "particles";
}

ParticleScreen::~ParticleScreen()
{
	TraceLog(LOG_INFO, "Closing ParticleScreen");
	generators.erase(generators.begin(),generators.end());
}
