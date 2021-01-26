#include <raylib.h>
#include "MainMenu.h"
#include "Manager.h"
#include "Menu.h"
#include "../globals.h"
#include "../screens/ScreenManager.h"
#include "../screens/CreditScreen.h"

MainMenu::MainMenu() {	
	name = "main";
	addChoice("1 player");
	addChoice("2 players");
	addChoice("head to head");
	addChoice("Settings", false);
	addChoice("Test Mode");	
	addChoice("Credits");
	addChoice("Quit", false);
}


void MainMenu::update() {
	
	Menu::update();
	
	if (pinManager.isButtonPressed(PIN_ENTER)) {
		if(choices.at(current)->name=="1 player")
			Menu::menumanager->setCurrent("1p");
		else if(choices.at(current)->name == "2 players")
			Menu::menumanager->setCurrent("2p");
		else if (choices.at(current)->name == "head to head")
			Menu::menumanager->setCurrent("head");
		else if (choices.at(current)->name == "Test Mode")
			Menu::menumanager->setCurrent("test");
		else if (choices.at(current)->name == "Credits") {
			CreditScreen* game1 = new CreditScreen();
			ScreenManager::Instance().addScreen(game1, "credit");			
			ScreenManager::Instance().setActive("credit");
		}
	}
}