#include "PinManager.h"

#ifdef PLATFORM_RPI
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#endif

#include <chrono>
#include <string>
#include <raylib.h>
#include "../globals.h"



void pin4(void)
{
	pins[4] = 0;	
}
void pin5(void)
{
	pins[5] = 0;
}
void pin6(void)
{
	pins[6] = 0;
}
void pin7(void)
{
	pins[7] = 0;
}
void pin8(void)
{
	pins[8] = 0;
}
void pin9(void)
{
	pins[9] = 0;
}
void pin10(void)
{
	pins[10] = 0;
}
void pin11(void)
{
	pins[11] = 0;
}


void PinManager::update()
{
	//std::chrono::time_point<std::chrono::high_resolution_clock> now;
	//now = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double> elapsed_seconds = now - last;

	
	for (unsigned int i = 0; i < gpio.size(); i++) {

		int state = 0;

#ifdef PLATFORM_RPI
		state = digitalRead(gpio[i]);
		if (i >= 4) {
			state = pins[i];
			pins[i] = 1; 			
		}
#else
#endif

		previousPinState[i] = currentPinState[i];		
		{
			if (previousPinState[i] != state) {
				currentPinState[i] = state;
			}
			
		}
	}

	

	
	
}

void PinManager::draw()
{
	//for (unsigned int i = 0; i < gpio.size(); i++) {
	//	DrawText(std::string("pin"+ std::to_string(gpio[i])+"=" + std::to_string(isButtonPressed(i))).c_str(), 50, 500+i*30, 30, BLACK);
	//}

	//DrawText(std::string("pin=" + std::to_string(pins_prev[0])).c_str(), 50, 470, 30, BLACK);
	//DrawText(std::string("pin=" + std::to_string(pins[0])).c_str(), 50, 500 , 30, BLACK);
	
	
}

 
 
bool PinManager::isButtonPressed(int pin)
{
	if ((previousPinState[pin]==1 && currentPinState[pin] == 0) || IsKeyPressed(keys[pin]))
	{		
		return true;
	}
	return false;
}



PinManager::PinManager() {

	
	
	TraceLog(LOG_INFO, "Initialing GPIO");

#ifdef PLATFORM_RPI
	TraceLog(INFO, "Initialing GPIO");
	wiringPiSetupGpio();
	for (unsigned int i = 0; i < gpio.size(); i++)
	{
		TraceLog(INFO, std::string("Setting pin " + std::to_string(gpio[i]) + " to INPUT").c_str());
		pinMode(gpio[i], INPUT);
		pullUpDnControl(gpio[i], PUD_UP);
	}	

	wiringPiISR(gpio[4], INT_EDGE_FALLING, &pin4);
	wiringPiISR(gpio[5], INT_EDGE_FALLING, &pin5);
	wiringPiISR(gpio[6], INT_EDGE_FALLING, &pin6);
	wiringPiISR(gpio[7], INT_EDGE_FALLING, &pin7);
	wiringPiISR(gpio[8], INT_EDGE_FALLING, &pin8);
	wiringPiISR(gpio[9], INT_EDGE_FALLING, &pin9);
	wiringPiISR(gpio[10], INT_EDGE_FALLING, &pin10);
	wiringPiISR(gpio[11], INT_EDGE_FALLING, &pin11);
#else	
#endif

	pins[0] = 1;
	//TraceLog(ERROR, "Initialing GPIO");
	debounce = 0.2f;
}





void PinManager::initialize()
{

}


