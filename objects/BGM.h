#pragma once

#include <raylib.h>

class BGM {

private:
	Sound sound;	
	float volume;
	bool play;

public:
	BGM();
	void init();
	virtual ~BGM();
	void fadeIn();
	void fadeOut();
	void update();
};
