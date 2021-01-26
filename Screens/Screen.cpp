#include "Screen.h"
#include <raylib.h>
#include <string>

void Screen::draw() {
	for (auto &p : items)
	{
		p->draw();
	}
}

std::string Screen::getName()
{
	return name;
}

void Screen::setName(std::string n)
{
	name = n;
}

void Screen::OnActive()
{
}

void Screen::OnDeactivate()
{
}

void Screen::update() {
	for (auto &p : items)
	{
		p->update();
	}
}

Screen::Screen() {
	isOverlay = false;
}

Screen::~Screen() {
	TraceLog(LOG_INFO, (std::string("deleted screen")+name).c_str());
}

void Screen::DrawTextExCentered(SpriteFont spriteFont, const char *text, Vector2 position, float fontSize, int spacing, Color tint) {
	Vector2 textSize = MeasureTextEx(spriteFont, text, fontSize, spacing);
	DrawTextEx(spriteFont, text, Vector2{ position.x - textSize.x / 2,position.y + textSize.y / 2 }, fontSize, spacing, tint);
}