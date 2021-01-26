#include <raylib.h>
#include <string>
#include "TestMenu.h"
#include "Manager.h"
#include "../screens/GameOverScreen.h"
#include "../screens/ScreenManager.h"
#include "../globals.h"

TestMenu::TestMenu() {
	name = "test";
	//addChoice("Particles");
	addChoice("LED");
	//addChoice("Score Counter");
	//addChoice("Game Over");
	addChoice("<Back>");
}

void TestMenu::update() {

	Menu::update();

	if (pinManager.isButtonPressed(PIN_BACK)) {
		Menu::menumanager->setCurrent("main");
	}

	if (pinManager.isButtonPressed(PIN_ENTER)) {
		
		if (choices.at(current)->name == "LED") {
			ScreenManager::Instance().setActive("led");
		}
		
		if (choices.at(current)->name == "<Back>") {
			Menu::menumanager->setCurrent("main");
		}
	}
}