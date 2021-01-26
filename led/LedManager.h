#pragma once

#include <array>
#include "../screens/Screen.h"
#include <raylib.h>
#include <string>

class LedManager {

private:	
	std::array<int,8> leds;
	LedManager() {};
	bool visible = false;

public:
	int fd;
	virtual void update();
	virtual void draw();
	virtual void close();
	void init(std::string device);
	void setColor(int n, Color c);

	static LedManager& Instance()
	{
		static LedManager singleton;
		return singleton;
	}


};