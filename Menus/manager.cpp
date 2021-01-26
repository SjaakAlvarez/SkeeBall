#include "Manager.h"
#include "../screens/ScreenManager.h"
#include "../globals.h"

void MenuManager::addMenu(Menu* m) {
	m->menumanager=this;
	menus.push_back(m);
}

void MenuManager::draw() {
	Menu* m = menus.at(current);
	m->draw();
}

void MenuManager::update() {
	Menu* m = menus.at(current);
	m->update();

	

}

MenuManager::~MenuManager() {
	for (unsigned int i = 0; i < menus.size(); i++)
	{
		//Menu* m = menus.at(i);
		//delete m;
	}
	menus.clear();
}

void MenuManager::setCurrent(int n) {
	current = n;
	Menu* m = menus.at(current);
	m->setCurrentChoice(0);
}

void MenuManager::setCurrent(std::string n) {
	for (unsigned int i = 0; i < menus.size(); i++)	{		
		Menu* m = menus.at(i);
		if (m->getName() == n) {
			setCurrent(i);
			break;
		}		
	}
}

MenuManager::MenuManager() {
	name = "menumanager";

	
}

void MenuManager::OnDeactivate() {
	TraceLog(LOG_INFO, "menumanager deactivated");
	bgm.fadeOut();
}

void MenuManager::OnActive() {
	TraceLog(LOG_INFO, "menumanager activated");
	bgm.fadeIn();
}