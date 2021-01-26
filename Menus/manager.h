#pragma once

#include <array>
#include "Menu.h"
#include "../screens/Screen.h"

class MenuManager : public Screen {

public:
	std::vector<Menu*> menus;
	int current=0;


	void addMenu(Menu* m);
	void update();
	void draw();
	void setCurrent(int n);
	void setCurrent(std::string n);
	virtual ~MenuManager();
	MenuManager();
	virtual void OnActive();
	virtual void OnDeactivate();
};
