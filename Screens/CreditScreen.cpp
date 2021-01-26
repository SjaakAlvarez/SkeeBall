#include "CreditScreen.h"

#define FONTSIZE 79

void CreditScreen::update()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> now;
	now = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed_seconds = now - last;

	/*for (unsigned int i = 0; i < generators.size(); i++)
	{
		generators[i]->update();
	}

	for (unsigned int i = 0; i < info.size(); i++)
	{
		if (info[i].t < 120 && info[i].t!=-1)
		{
			info[i].pos.y = EaseElasticOut(info[i].t, info[i].start.y, info[i].end.y - info[i].start.y, 120);
			info[i].t++;
		}
		if (info[i].t == -1 && info[i].delay < elapsed_seconds.count()) {
			info[i].t = 0;
		}
	}*/
	for(int i=0;i<3;i++)
	sprite[i].update();

	if (pinManager.isButtonPressed(PIN_BACK) || pinManager.isButtonPressed(PIN_ENTER)) {
		ScreenManager::Instance().setActive("menumanager");
		ScreenManager::Instance().removeScreen("credit");
		delete this;
	}

}

void CreditScreen::draw()
{
	
	ClearBackground(WHITE);
	DrawTexture(texturebk, 0, 0, WHITE);

	//DrawTextEx(rocket, "ELECTRONICS", Vector2{ 600,200 }, FONTSIZE/2, 0, RAYWHITE);
	//DrawTextEx(rocket, "SCOTT (PL1)", Vector2{ 600,225 }, FONTSIZE, 0, RAYWHITE);
	//DrawTextEx(rocket, "SOFTWARE", Vector2{ 600,300  }, FONTSIZE/2, 0, RAYWHITE);
	//DrawTextEx(rocket, "SJAAK", Vector2{ 600,325 }, FONTSIZE, 0, RAYWHITE);

	/*BeginBlendMode(BLEND_ADDITIVE);
	for (unsigned int i = 0; i < generators.size(); i++)
	{
		generators[i]->draw();
	}
	EndBlendMode();*/

	DrawText("© 2017 Sjaak Alvarez", 370, 280, 20, WHITE);
	DrawText("Gameplay - Scott (PL1)", 370, 310, 20, RAYWHITE);
	DrawText("Electronics - Scott (PL1)", 370, 335, 20, RAYWHITE);
	DrawText("Software Development - Sjaak Alvarez", 370, 360, 20, RAYWHITE);
	DrawText("This work is licensed under a Creative Commons", 370, 630, 20, LIGHTGRAY);
	DrawText("Attribution-NonCommercial-NoDerivatives 4.0 International License.", 370, 655, 20, LIGHTGRAY);
	

	DrawTexture(texture, 1100, 630, WHITE);

	/*for (unsigned int i = 0; i < info.size(); i++)
	{
		Vector2 textSize = MeasureTextEx(rocket, info[i].text.c_str(), FONTSIZE, 0);		
		DrawTextEx(rocket, info[i].text.c_str(), Vector2{ info[i].pos.x-(textSize.x/2),info[i].pos.y+(textSize.y/2) }, FONTSIZE, 0, RAYWHITE);
	}*/
	for (int i = 0; i<3; i++)
		sprite[i].draw();
	

	DrawTexture(texOverlay, 0, 0, WHITE);

}

CreditScreen::CreditScreen()
{
	name = "credit";
	rocket = LoadFont("resources/silver40.fnt");
	texturebk = LoadTexture("resources/credit/background.png");
	texOverlay = LoadTexture("resources/credit/overlay.png");
	textureStar = LoadTexture("resources/credit/star.png");

	texture = LoadTexture("resources/by-nc-nd-small.png");

	isOverlay = false;

	std::array<std::string, 5> msg{ "Software Development","Sjaak","","Electronics","Scott - PL1" };

	for (unsigned int i = 0; i < msg.size(); i++) {
		info[i].text = msg[i];
		info[i].delay = 2-(i/5.0f);
		info[i].start = Vector2{ 640,(float)-120 };
		info[i].end = Vector2{ 640,(float)(200+FONTSIZE*i)-100 };
		info[i].pos = info[i].start;
		info[i].t = -1;
	}

	for (int i = 0; i < 3; i++)
		sprite[i].pos = Vector2{ 100.0f + 205.0f * i,400.0f };

	last = std::chrono::high_resolution_clock::now();

	for (unsigned int i = 0; i < 7; i++) {
		std::shared_ptr<ParticleGenerator> gen = std::make_shared<ParticleGenerator>();
		gen->particlesPerSecond = 1000;
		gen->maxParticles = 100;
		gen->gravity = 0.1f;
		gen->color = WHITE;
		gen->delay = 1.4+0.25*i;
		gen->maxAge = 1.5;
		gen->setTexture(textureStar);
		gen->randomColor = false;
		gen->particleSize = Vector2{ 32,32 };
		gen->position = Vector2{ (float)GetRandomValue(100,1180),(float)GetRandomValue(100,520) };
		generators.push_back(gen);
	}
}

CreditScreen::~CreditScreen()
{
	UnloadTexture(texture);
	UnloadFont(rocket);
	UnloadTexture(textureStar);
	UnloadTexture(texOverlay);
	UnloadTexture(texturebk);
	generators.erase(generators.begin(), generators.end());
}
