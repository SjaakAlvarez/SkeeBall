#pragma once

#include "Screen.h"
#include <chrono>
#include <raylib.h>
#include <memory>
#include <array>

class LicenseScreen :public Screen {

private:	
	std::chrono::time_point<std::chrono::high_resolution_clock> last = std::chrono::high_resolution_clock::now();

	
	Texture2D texture;
	

public:
	virtual void update();
	virtual void draw();
	LicenseScreen();
	virtual ~LicenseScreen();
	

};