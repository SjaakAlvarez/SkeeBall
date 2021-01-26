#include "LicenseScreen.h"
#include "ScreenManager.h"
#include <easings.h>
#include "../globals.h"

void LicenseScreen::update()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> now;
	now = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - last;
	
	if (elapsed_seconds.count() > 5) {
		//ScreenManager::Instance().setActive("menumanager");
		ScreenManager::Instance().removeScreen("license");
		delete this;
	}

}


void LicenseScreen::draw()
{
	int textSize = 120;	
	int x = 0;

	DrawRectangle(350, 260,580, 200, RAYWHITE);
	DrawRectangleLines(350, 260, 580, 200, BLACK);

	DrawText("© 2017 Sjaak Alvarez",370,280,20,BLACK);
	DrawText("This work is licensed under a Creative Commons", 370, 330, 20, BLACK);
	DrawText("Attribution-NonCommercial-NoDerivatives", 370, 355, 20, BLACK);
	DrawText("4.0 International License.", 370, 380, 20, BLACK);
	
	//DrawTextExCentered(rocket, texts[displayText].c_str(), Vector2{ (float)x + 2,362 }, textSize, 0, BLACK);
	//DrawTextExCentered(rocket, texts[displayText].c_str(), Vector2{ (float)x,240 }, textSize, 0, RAYWHITE);
	DrawTexture(texture, 780, 400, WHITE);
}

LicenseScreen::LicenseScreen()
{
	name = "license";
	isOverlay = true;	

	texture=LoadTexture("resources/by-nc-nd-small.png");
}

LicenseScreen::~LicenseScreen()
{
	UnloadTexture(texture);
}

