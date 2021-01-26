#include "ScreenManager.h"
#include <raylib.h>
#include <string>

void ScreenManager::draw() {
	Screen* s = screens.at(active);
	s->draw();

	

	for (unsigned int i = 0; i < screens.size(); i++) {
		if (screens.at(i)->isOverlay) {
			screens.at(i)->draw();
		}
	}

	if (visible) {
		DrawFPS(1100, 20);
		
		DrawRectangle(1090, 490, 150, 200, CLITERAL(Color){ 0,0,0,240 });
		DrawRectangleLines(1090, 490, 150, 200, CLITERAL(Color){ 255,0,255,200 });

		for (unsigned int i = 0; i < screens.size(); i++) {
			if (screens.at(i)->isActive)
			{
				if(screens.at(i)->isOverlay)
					DrawText((std::string("Scr ") + screens.at(i)->getName()+" *").c_str(), 1100, 500 + 10 * i, 10, WHITE);
				else
					DrawText((std::string("Scr ") + screens.at(i)->getName()).c_str(), 1100, 500 + 10 * i, 10, WHITE);
			}
			else {
				if (screens.at(i)->isOverlay)
					DrawText((std::string("Scr ") + screens.at(i)->getName()+" *").c_str(), 1100, 500 + 10 * i, 10, GRAY);
				else
					DrawText((std::string("Scr ") + screens.at(i)->getName()).c_str(), 1100, 500 + 10 * i, 10, GRAY);
			}
		}
	}
}



void ScreenManager::update() {
	Screen* s = screens.at(active);
	s->update();

	for (unsigned int i = 0; i < screens.size(); i++) {
		if (screens.at(i)->isOverlay) {
			screens.at(i)->update();
		}
	}

	if (IsKeyPressed(KEY_F5)) {
		visible = !visible;
	}

	
}

void ScreenManager::addScreen(Screen* s) {	
	screens.push_back(s);
}

void ScreenManager::addScreen(Screen* s, std::string n) {
	s->setName(n);
	screens.push_back(s);
}

void ScreenManager::removeScreen(std::string n)
{
	for (unsigned int i = 0; i < screens.size(); i++) {
		Screen* m = screens.at(i);
		if (m->getName() == n) {
			screens.erase(screens.begin() + i);
			break;
		}
	}
}

void ScreenManager::setActive(int n) {
	active = n;
}

void ScreenManager::setActive(std::string n) {

	screens.at(active)->isActive = false;
	screens.at(active)->OnDeactivate();

	for (unsigned int i = 0; i < screens.size(); i++) {
		Screen* m = screens.at(i);
		if (m->getName() == n) {
			setActive(i);
			m->isActive = true;
			m->OnActive();
		}		
	}
}

