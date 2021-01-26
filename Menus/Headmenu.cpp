#include <raylib.h>
#include <string>
#include "TestMenu.h"
#include "Manager.h"
#include "../screens/ScreenManager.h"
#include "HeadMenu.h"
#include "Menu.h"
#include "../globals.h"
#include "../screens/LockoutGame.h"

void HeadMenu::update() {

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

HeadMenu::HeadMenu()
{
	name = "head";
	addChoice("Lockout");
	addChoice("Gunslinger", false);
	addChoice("Head-to-Head Race", false);
	addChoice("<Back>");
}
