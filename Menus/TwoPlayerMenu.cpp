#include <raylib.h>
#include <string>
#include "TestMenu.h"
#include "Manager.h"
#include "../screens/ScreenManager.h"
#include "TwoPlayerMenu.h"
#include "Menu.h"
#include "../globals.h"
#include "../screens/LockoutGame.h"

void TwoPlayerMenu::update() {

	Menu::update();

	if (pinManager.isButtonPressed(PIN_BACK)) {
		Menu::menumanager->setCurrent("main");
	}

	if (pinManager.isButtonPressed(PIN_ENTER)) {
		if (choices.at(current)->name == "<Back>") {
			Menu::menumanager->setCurrent("main");
		}
		if (choices.at(current)->name == "Lockout") {
			LockoutGame* game1 = new LockoutGame();
			ScreenManager::Instance().addScreen(game1, "lockout");			
			ScreenManager::Instance().setActive("lockout");
		}

	}
}

TwoPlayerMenu::TwoPlayerMenu()
{
	name = "2p";
	
	addChoice("Tic Tac 3", false);
	addChoice("Tic Tac Seek",false);
	addChoice("Horse", false);
	addChoice("Blackjack", false);
	addChoice("Ball Fighter", false);
	addChoice("<Back>");
}
