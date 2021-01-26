#include "BGM.h"

BGM::BGM()
{
	TraceLog(LOG_INFO, "constructed BGM");
}

BGM::~BGM()
{
	UnloadSound(sound);
	TraceLog(LOG_INFO,"deconstructed BGM");
}

void BGM::init() {
	sound = LoadSound("resources/music/Circus-music.ogg");	
	PlaySound(sound);	
	volume = 0.0f;
	SetSoundVolume(sound, 0);
	play = true;
}

void BGM::fadeIn()
{
	TraceLog(LOG_INFO, "fadeIn BGM");
	play = true;
	volume = 0.0f;
	SetSoundVolume(sound, 0);
	PlaySound(sound);
}

void BGM::fadeOut()
{
	TraceLog(LOG_INFO, "fadeOut BGM");
	play = false;
}

void BGM::update()
{

	if (play) {
		if (volume < 1.0f) {
			volume += 0.005;
			SetSoundVolume(sound, volume);			
		}		
	}
	else {
		if (volume > 0) {
			volume -= 0.01f;
			SetSoundVolume(sound, volume);			
			if (volume <= 0) {
				StopSound(sound);
				SetSoundVolume(sound, 0);				
				volume = 0;
			}
		}
	}
}
