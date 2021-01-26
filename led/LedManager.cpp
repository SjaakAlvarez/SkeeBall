#include "LedManager.h"
#include <raylib.h>
#include <string>
#include <chrono>
#include <thread>

#ifdef PLATFORM_RPI
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>
#endif


void LedManager::init(std::string device) {

#ifdef PLATFORM_RPI
	//fd = serialOpen("/dev/ttyACM0", 19200);
	fd = serialOpen(device.c_str(), 19200);
	usleep(1000000);
	if (fd == -1)TraceLog(WARNING, std::string("Cannot open "+device).c_str());
	for (int i = 0; i < 8; i++) {
		serialPuts(fd, "C");
		usleep(10000);
	}
#else
	std::this_thread::sleep_for(std::chrono::milliseconds(800));
#endif


	for (unsigned int i = 0; i < 8; i++){
		leds.at(i) = 0xff;
	}
}

void LedManager::close() {
	
#ifdef PLATFORM_RPI
	for (unsigned int i = 0; i < 8; i++) {
		serialPuts(fd, "O");
		serialPutchar(fd, (char)i);
		serialPutchar(fd, (char)0);
		serialPutchar(fd, (char)0);
		serialPutchar(fd, (char)0);
	}
	
	serialClose(fd);
#endif

}

void LedManager::draw() {

	if (visible) {
		DrawRectangle(900, 60, 320, 20, BLACK);
		DrawRectangleLines(900, 60, 320, 20, GRAY);
		for (unsigned int i = 0; i < leds.size(); i++) {
			DrawRectangle(902 + (20 * i), 62, 16, 16,GetColor(leds.at(i)));
			DrawRectangleLines(902 + (20 * i), 62, 16, 16, GRAY);
		}
	}
}

void LedManager::update() {
	if (IsKeyPressed(KEY_F6)) {
		visible = !visible;
	}
}


void LedManager::setColor(int n, Color c) {

#ifdef PLATFORM_RPI
	serialPutchar(fd, 'O');
	serialPutchar(fd, (char)n);
	serialPutchar(fd, (char)c.r);
	serialPutchar(fd, (char)c.g);
	serialPutchar(fd, (char)c.b);
#else
	std::this_thread::sleep_for(std::chrono::milliseconds(2));
#endif
	
	leds.at(n) = ColorToInt(c);
}
