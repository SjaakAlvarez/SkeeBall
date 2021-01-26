#include "MoleGame.h"
#include "../globals.h"
#include "ScreenManager.h"
#include <math.h>  

void MoleGame::OnStart() {
	TraceLog(LOG_INFO, "MoleGame OnStart");
	newMole();
	last = std::chrono::high_resolution_clock::now();
}

void MoleGame::OnQuit() {
	TraceLog(LOG_INFO, "MoleGame OnQuit");
	ScreenManager::Instance().setActive("menumanager");
	ScreenManager::Instance().removeScreen("mole");	
	delete this;
}


void MoleGame::newMole() {
	int rand = GetRandomValue(0, 5);
	while (rand == activeMole) {
		rand = GetRandomValue(0, 5);
	}
	activeMole = rand;	
}

void MoleGame::update()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> now;
	now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - last;

	if (gameState == GameState::PLAYING)
	{

		for (unsigned int i = 0; i < 8; i++) {
			if (pinManager.isButtonPressed(sensorsP1[i])) {
				if (activeMole == ballmap[i])
				{
					generateBoom(Vector2{ moles[activeMole].pos.x + 160,moles[activeMole].pos.y + 100 });
					scoreP1 += scores[i];
					last = now;
					newMole();
				}
				counterBalls->count--;
			}
		}

		if (elapsed_seconds.count() > 5)
		{
			last = now;
			newMole();
		}

		counterP1->count = scoreP1;
		clock->update();


		if (clock->count == 0 || counterBalls->count <= 0) {			
			activeMole = -1;
			endGame();
		}
	}

	for (unsigned int i = 0; i < 6; i++) {
		if (i == activeMole) {
			if (moles[i].frame < 10) moles[i].frame++;
		}
		else {
			if (moles[i].frame > 0) moles[i].frame--;
		}
	}

	counterP1->update();
	counterBalls->update();

	for (auto &p : generators) p->update();

	Game::update();

}

void MoleGame::draw()
{
	DrawTexture(texturebk, 0, 0, WHITE);
	for (unsigned int i = 0; i < 6; i++) {
		{
			Rectangle rect{ (moles[i].frame % 3) * 320,(floor(moles[i].frame / 3)) * 256,320,256 };
			DrawTextureRec(textureMole, rect, moles[i].pos, WHITE);

			Rectangle rect2{ 0,i * 128,256,128 };
			Vector2 pos2{ moles[i].pos.x + 32 ,moles[i].pos.y + 160 };
			DrawTextureRec(texturePoints, rect2, pos2, WHITE);
		}

	}
	clock->draw();
	counterP1->draw();
	counterBalls->draw();

	for (auto &p : generators) p->draw();


	
}

MoleGame::MoleGame()
{
	texturebk = LoadTexture("resources/whackamole/background.png");
	textureMole = LoadTexture("resources/whackamole/mole.png");
	texturePoints = LoadTexture("resources/whackamole/points.png");
	textureStar = LoadTexture("resources/whackamole/star.png");

	clock = new Clock();
	clock->pos = Vector2{ 512,25 };
	clock->count = 120;
	clock->clockSize = 60;
	clock->initialize();

	counterP1 = new Counter();
	counterBalls = new Counter();

	counterP1->pos = Vector2{ 243,25 };
	counterP1->width = 4;
	counterP1->counterSize = 60;
	counterP1->animated = true;
	counterP1->count_increment = 500;
	counterP1->initialize();

	counterBalls->pos = Vector2{ 1187,25 };
	counterBalls->width = 1;
	counterBalls->count = 9;
	counterBalls->counterSize = 60;
	counterBalls->animated = false;
	counterBalls->initialize();

	moles[0].frame = 0;
	moles[0].pos = Vector2{ 100,130 };
	moles[1].frame = 0;
	moles[1].pos = Vector2{ 480,180 };
	moles[2].frame = 0;
	moles[2].pos = Vector2{ 860,130 };
	moles[3].frame = 0;
	moles[3].pos = Vector2{ 100,400 };
	moles[4].frame = 0;
	moles[4].pos = Vector2{ 480,450 };
	moles[5].frame = 0;
	moles[5].pos = Vector2{ 860,400 };

	isTwoPlayer = false;
	scoreUnit = "point";
	scoreUnitPlural = "points";
	activeMole = -1;
	initGame();
}

MoleGame::~MoleGame()
{
	generators.erase(generators.begin(), generators.end());
	delete counterBalls;
	delete counterP1;
	delete clock;
	UnloadTexture(textureStar);
	UnloadTexture(texturePoints);
	UnloadTexture(textureMole);
	UnloadTexture(texturebk);
}

void MoleGame::generateBoom(Vector2 pos) {
	std::shared_ptr<ParticleGenerator> gen = std::make_shared<ParticleGenerator>();
	gen->particlesPerSecond = 1000;
	gen->maxParticles = 10;
	gen->color = WHITE;
	gen->delay = 0.0;
	gen->maxAge = 0.7f;
	gen->speed = 50;
	gen->gravity = 0.1f;
	gen->randomColor = false;
	gen->particleSize = Vector2{ 64,64 };
	gen->position = pos;
	gen->setTexture(textureStar);
	generators.push_back(gen);
}