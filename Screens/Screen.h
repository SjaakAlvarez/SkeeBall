#pragma once
#include <string>
#include <vector>
#include <map>
#include "../objects/Drawable.h"
#include <raylib.h>

class Screen {

protected:
	std::string name;
	std::vector<Drawable*> items;
	
public:
	bool isOverlay=false;
	bool isActive;

	virtual void OnActive();
	virtual void OnDeactivate();

	virtual void update();
	virtual void draw();
	std::string getName();
	void setName(std::string);
	Screen();
	virtual ~Screen();

	void DrawTextExCentered(SpriteFont spriteFont, const char * text, Vector2 position, float fontSize, int spacing, Color tint);

};

