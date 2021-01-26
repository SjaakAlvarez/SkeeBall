#include "TimeBomb.h"
#include "../globals.h"
#include "ScreenManager.h"
#include <math.h>  
#include <easings.h>

void TimeBomb::OnStart() {
	TraceLog(LOG_INFO, "TimeBomb OnStart");
	last = std::chrono::high_resolution_clock::now();
}

void TimeBomb::OnQuit() {
	TraceLog(LOG_INFO, "TimeBomb OnQuit");
	ScreenManager::Instance().setActive("menumanager");
	ScreenManager::Instance().removeScreen("timebomb");	
	delete this;
}


void TimeBomb::createNewSequence() {
	activeCode = 0;
	disarmCode.clear();
	if (level < 5) {
		for (int i = 0; i < 3; i++) {
			disarmCode.push_back(GetRandomValue(0, 4));
		}
	}
	else if (level < 10) {
		for (int i = 0; i < 4; i++) {
			disarmCode.push_back(GetRandomValue(0, 4));
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			disarmCode.push_back(GetRandomValue(0, 5));
		}
	}
	
}

void TimeBomb::startNewLevel() {
	clock->count = 60;
	createNewSequence();
	state = State::STARTLEVEL;
	last = std::chrono::high_resolution_clock::now();
}

void TimeBomb::update()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> now;
	now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - last;

	if (gameState == GameState::PLAYING)
	{


		if (state == State::PLAYING) {
			bool hit = true;
			for (unsigned int i = 0; i < 8; i++) {
				if (pinManager.isButtonPressed(sensorsP1[i])) {
					if (disarmCode.at(activeCode) == ballmap[i])
					{
						activeCode++;
						if (activeCode >= disarmCode.size()) {
							level++;
							startNewLevel();
						}
					}
					else {
						hit = false;
					}

				}
			}
			if (!hit) {
				activeCode = 0;
			}
			clock->update();
		}
		else if (state == State::STARTLEVEL) {
			if (elapsed_seconds.count() > 3) {
				state = State::PLAYING;
			}
		}

		//lights animation
		t++;
		if (t % 30 == 0) t1 = !t1;
		if (t % 55 == 0) t2 = !t2;
		if (t % 55 == 0) t3 = !t3;

		

		if (clock->count == 0) {	
			scoreP1 = level;
			endGame();
		}
	}

	

	
	

	Game::update();

}

void TimeBomb::draw()
{
	DrawTexture(texturebk, 0, 0, WHITE);
	
	if (t1) DrawTexture(textureLed1, 240, 0, WHITE);
	if (t2) DrawTexture(textureLed2, 640, 160, WHITE);
	if (t3) DrawTexture(textureLed3, 720, 480, WHITE);



	clock->draw();
	
	if (state == State::PLAYING) {
		for (int i = 0; i < disarmCode.size(); i++) {
			//DrawText(std::to_string(disarmCode.at(i)).c_str(), i * 80, 100, 40, RED);
			if (i < activeCode) {
				DrawText(std::to_string(disarmValues[disarmCode.at(i)]).c_str(), 1100, 40 + 40 * i, 40, DARKGRAY);
			}
			else
			{
				DrawText(std::to_string(disarmValues[disarmCode.at(i)]).c_str(), 1100, 40 + 40 * i, 40, WHITE);
			}
		}
	}
	else if (state == State::STARTLEVEL) {
		DrawText(("Level "+std::to_string(level+1)).c_str(), 500, 300, 70, WHITE);
	}
	
	
}

TimeBomb::TimeBomb()
{
	texturebk = LoadTexture("resources/timebomb/background.png");
	textureLed1 = LoadTexture("resources/timebomb/red1_on.png");
	textureLed2 = LoadTexture("resources/timebomb/green1_on.png");
	textureLed3 = LoadTexture("resources/timebomb/green2_on.png");

	clock = new Clock();
	clock->pos = Vector2{ 713,96 };
	clock->count = 10;
	clock->clockSize = 40;
	clock->initialize();
	
	isTwoPlayer = false;
	scoreUnit = "level";
	scoreUnitPlural = "levels";

	t = 0;
	t1 = true;
	t2 = false;
	t3 = true;
	level = 0;
	
	startNewLevel();	

	initGame();
}

TimeBomb::~TimeBomb()
{
	generators.erase(generators.begin(), generators.end());
	
	delete clock;
	UnloadTexture(textureLed3);
	UnloadTexture(textureLed2);
	UnloadTexture(textureLed1);
	UnloadTexture(texturebk);
}

