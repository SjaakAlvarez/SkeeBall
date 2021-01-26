#pragma once

#include <vector>
#include "Screen.h"
#include <string>
#include <raylib.h>

class ScreenManager {

private:
	unsigned int active=0;
	std::vector<Screen*> screens;
	ScreenManager() {};
	bool visible=false;
	void setActive(int n);
public:
	
	
	virtual void update();
	virtual void draw();
	void addScreen(Screen* s);
	void addScreen(Screen * s, std::string n);
	void removeScreen(std::string n);
	
	void setActive(std::string n);
	static ScreenManager& Instance()
	{
		static ScreenManager singleton;		
		return singleton;
	}
	
	
};