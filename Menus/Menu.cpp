#include <string>
#include <vector>
#include <iostream>
#include "raylib.h"
#include "Menu.h"
#include "Manager.h"
#include "../globals.h"
#include <easings.h>
#include <memory>

Menu::Menu() {
	TraceLog(LOG_INFO, "default constructor");
	rocket = LoadFont("resources/silver40.fnt");
	//rocket = LoadSpriteFontEx("resources/Supersonic Rocketship.ttf", 50, 0, 0);
}



void Menu::addChoice(std::string choice) {
	std::shared_ptr<Option> option = std::make_shared<Option>();
	option->name = choice;
	option->displayName = choice;
	option->enabled = true;
	choices.push_back(option);
}
void Menu::addChoice(std::string choice, bool v)
{
	std::shared_ptr<Option> option = std::make_shared<Option>();
	option->name = choice;
	option->displayName = choice;
	option->enabled = v;
	choices.push_back(option);
}
std::string Menu::getName()
{
	return name;
}
void Menu::setCurrentChoice(int n) {
	current = n;
}

void Menu::draw() {
	int y = (620-(choices.size()*50))/2;
	for (unsigned int i = 0; i < choices.size(); i++) {

		//int s = 50+ sin(t/10.0)*5;

		Color color = WHITE;
		
		
		
		if (i == current) {
			if (!choices.at(i)->enabled) color = Color{ 255,255,255,128 };
			Vector2 textSize = MeasureTextEx(rocket, choices.at(i)->displayName.c_str(), 79, 0);

			Vector2 pos1{ 642.0f - (textSize.x / 2), y + 2.0f + 50.0f * i + (textSize.y / 2) };
			Vector2 pos2{ 640.0f - (textSize.x / 2), y + 50.0f * i + (textSize.y / 2) };

			//DrawTextEx(rocket, choices.at(i).c_str(), pos1, 79, 0, BROWN);
			DrawTextEx(rocket, choices.at(i)->displayName.c_str(), pos2, 79, 0, color);
		}
		else {
			if (!choices.at(i)->enabled) color = Color{ 130,130,130,128 }; else color = Color{ 130,130,130,255 };
			Vector2 textSize = MeasureTextEx(rocket, choices.at(i)->displayName.c_str(), 79, 0);

			Vector2 pos2{ 640.0f - (textSize.x / 2), y + 50.0f * i + (textSize.y / 2) };

			DrawTextEx(rocket, choices.at(i)->displayName.c_str(), pos2, 79, 0, color);
		}		
	}
}

void Menu::update() {

	if (t < 30) t++; else t = 0;

	if (pinManager.isButtonPressed(PIN_UP) && current>0) {
		current--;
		t = 0;
	}
	if (pinManager.isButtonPressed(PIN_DOWN) && current<choices.size()-1) {
		current++;
		t = 0;
	}

}
	
Menu::~Menu() {
	UnloadFont(rocket);
	choices.erase(choices.begin(), choices.end());
	TraceLog(LOG_INFO, "menu deleted");
}




