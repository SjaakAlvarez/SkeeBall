#include <raylib.h>
#include <string>
#include "TestMenu.h"
#include "Manager.h"
#include "../screens/ScreenManager.h"
#include "OnePlayerMenu.h"
#include "Menu.h"
#include "../screens/OldSkoolGame.h"
#include "../screens/ThreeTen.h"
#include "../screens/MoleGame.h"
#include "../screens/TimeBomb.h"
#include "../globals.h"

void OnePlayerMenu::update() {

	Menu::update();

	if (pinManager.isButtonPressed(PIN_BACK)) {
		Menu::menumanager->setCurrent("main");
	}

	if (pinManager.isButtonPressed(PIN_ENTER)) {
		if (choices.at(current)->name == "<Back>") {
			Menu::menumanager->setCurrent("main");			
		}
		if (choices.at(current)->name == "Old School") {
			OldSkoolGame* game1 = new OldSkoolGame();
			ScreenManager::Instance().addScreen(game1,"oldskool"); 			
			ScreenManager::Instance().setActive("oldskool");
		}
		else if (choices.at(current)->name == "310") {
			ThreeTen* game1 = new ThreeTen();
			ScreenManager::Instance().addScreen(game1, "threeten");			
			ScreenManager::Instance().setActive("threeten");
		}
		else if (choices.at(current)->name == "Whack A Hole") {
			MoleGame* game1 = new MoleGame();
			ScreenManager::Instance().addScreen(game1, "mole");
			ScreenManager::Instance().setActive("mole");
		}
		else if (choices.at(current)->name == "Time Bomb") {
			TimeBomb* game1 = new TimeBomb();
			ScreenManager::Instance().addScreen(game1, "timebomb");
			ScreenManager::Instance().setActive("timebomb");
		}
	}
}

OnePlayerMenu::OnePlayerMenu()
{
	name = "1p";
	addChoice("Whack A Hole");
	addChoice("Old School");	
	//addChoice("Go/No-Go",false);
	addChoice("310");
	//addChoice("Cliffhanger", false);
	//addChoice("Three Ball", false);
	//addChoice("Cricket", false);
	//addChoice("Flash", false);
	addChoice("Time Bomb");
	//addChoice("Quick-Draw", false);
	addChoice("<Back>");
}
