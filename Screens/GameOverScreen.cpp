#include "GameOverScreen.h"
#include "ScreenManager.h"
#include <easings.h>
#include "../globals.h"

void GameOverScreen::update()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> now;
	now = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed_seconds = now - last;

	if (t < 90) t++;

	for (unsigned int i = 0; i < generators.size(); i++)
	{
		generators[i]->update();
	}

}


void GameOverScreen::draw()
{
	int y = EaseBounceOut(t, -720, 720, 90);
	int alpha = EaseQuadIn(t, 0, 230, 90);

	DrawTexture(texturebk, 0, 0, Color{255,255,255,(unsigned char)alpha});
	DrawTexture(texturebox, 0, y, WHITE);
	
	//DrawTextExCentered(rocket, "GAME OVER", Vector2{ 642,282 + (float)y }, 50, 0, BROWN);
	DrawTextExCentered(rocket, "game over", Vector2{ 640,220+(float)y }, 79, 0, WHITE);

	std::string p1 = "player 1 - " + std::to_string(scoreP1) +" "+ std::string(scoreP1 == 1 ? scoreUnit:scoreUnitPlural);
	std::string p2 = "player 2 - " + std::to_string(scoreP2) + " "+std::string(scoreP2 == 1 ? scoreUnit : scoreUnitPlural);

	DrawTextExCentered(rocket, p1.c_str(), Vector2{ 642,300 + (float)y+2 }, 79, 0, WHITE);
	//DrawTextExCentered(rocket, p1.c_str(), Vector2{ 640,360+(float)y }, 50, 0, BEIGE);
	if (isTwoPlayer) {
		DrawTextExCentered(rocket, p2.c_str(), Vector2{ 642,360 + (float)y +2}, 79, 0, WHITE);
		//DrawTextExCentered(rocket, p2.c_str(), Vector2{ 640,420+(float)y }, 50, 0, BEIGE);
	}

	for (unsigned int i = 0; i < generators.size(); i++)
	{
		generators[i]->draw();
	}
	
}

GameOverScreen::GameOverScreen()
{
	name = "gameover";
	rocket = LoadFont("resources/fonts/silver40.fnt");
	texturebk = LoadTexture("resources/gameover/background.png");
	texturebox = LoadTexture("resources/gameover/box.png");
	isOverlay = true;	
	state = 0;
	t = 0;

	for (unsigned int i = 0; i < 7; i++) {
		std::shared_ptr<ParticleGenerator> gen = std::make_shared<ParticleGenerator>();
		gen->particlesPerSecond = 1000;
		gen->maxParticles = 60;
		gen->gravity = 0.1f;
		gen->color = GREEN;
		gen->delay = 0.5;
		gen->randomColor = true;
		gen->particleSize = Vector2{ 20,10 };
		gen->position = Vector2{ (float)GetRandomValue(100,1180),(float)GetRandomValue(100,520) };
		generators.push_back(gen);
	}
}

GameOverScreen::~GameOverScreen()
{
	UnloadFont(rocket);
	UnloadTexture(texturebox);
	UnloadTexture(texturebk);
	TraceLog(LOG_INFO, "Closing GameOverScreen");
	generators.erase(generators.begin(), generators.end());
}

void GameOverScreen::setInfo(int s1, int s2, std::string unit, std::string unitPlural, bool is2p)
{
	scoreP1 = s1;
	scoreP2 = s2;
	scoreUnit = unit;
	scoreUnitPlural = unitPlural;
	isTwoPlayer = is2p;
}
