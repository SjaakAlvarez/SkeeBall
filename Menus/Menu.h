#pragma once
#include <string>
#include <vector>
#include <ctype.h>
#include <raylib.h>
#include <memory>

class MenuManager;

class Option {
public:
	std::string name;
	bool enabled;
	std::string displayName;
};

class Menu {

protected:
	std::string name = "menuname";
	unsigned int current = 0;
	std::vector<std::shared_ptr<Option>> choices;
	SpriteFont rocket;
	unsigned int t;

public:
	MenuManager* menumanager;

	void addChoice(std::string choice);
	void addChoice(std::string choice, bool v);
	std::string getName();
	virtual void draw();
	virtual void update();	
	void setCurrentChoice(int n);
	Menu();
	virtual ~Menu();
	
	
};
