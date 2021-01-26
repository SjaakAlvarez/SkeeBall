#include "raylib.h"
#include "menus/Menu.h"
#include "menus/MainMenu.h"
#include "menus/Manager.h"
#include "menus/TestMenu.h"
#include "menus/OnePlayerMenu.h"
#include "menus/TwoPlayerMenu.h"
#include "menus/HeadMenu.h"
#include "screens/ScreenManager.h"
#include "screens/ScoreScreen.h"
#include "screens/ParticleScreen.h"
#include "screens/LedScreen.h"
#include "led/LedManager.h"
#include "screens/OldSkoolGame.h"
#include "objects/ParticleGenerator.h"
#include "util/Config.h"
#include "util/PinManager.h"
#include "screens/LicenseScreen.h"

#include <chrono>
#include <thread>


Config config;
PinManager pinManager;
BGM bgm;


int main(int argc, char* argv[])
{
	int screenWidth = 1280;
	int screenHeight = 720;

	config.initialize("config.txt");
	std::string appName = config.getString("appname");

	InitWindow(screenWidth, screenHeight, appName.c_str());
	InitAudioDevice();

	bgm.init();
	bgm.fadeIn();


	//Sound ding = LoadSound("resources/87.ogg");
	//PlaySound(ding);
	SetTargetFPS(60);

	Texture2D texture = LoadTexture("resources/skeeball.png");
	Texture2D texturebk = LoadTexture("resources/background.png");

	ScreenManager* screenManager = &ScreenManager::Instance();

	LedManager* ledManager = &LedManager::Instance();
	ledManager->init(config.getString("arduino"));// "/dev/ttyACM0");

	MenuManager* menumanager = new MenuManager();
	MainMenu mainMenu = MainMenu();	
	menumanager->addMenu(&mainMenu);
	OnePlayerMenu onePlayerMenu = OnePlayerMenu();	
	menumanager->addMenu(&onePlayerMenu);
	TwoPlayerMenu twoPlayerMenu = TwoPlayerMenu();	
	menumanager->addMenu(&twoPlayerMenu);
	HeadMenu headMenu = HeadMenu();
	menumanager->addMenu(&headMenu);
	TestMenu testMenu = TestMenu();	
	menumanager->addMenu(&testMenu);

	LedScreen* ledScreen = new LedScreen();

	//SpriteFont test = LoadSpriteFont("resources/fonts/metal30.fnt");
	//SpriteFont test2 = LoadSpriteFontEx("resources/Supersonic Rocketship.ttf",48,0,0);

	//LicenseScreen* license = new LicenseScreen();

	screenManager->addScreen(menumanager);
	screenManager->addScreen(ledScreen);
	//screenManager->addScreen(license);

	screenManager->setActive("menumanager");
	
	while (!WindowShouldClose())
	{
		bgm.update();

		screenManager->update();
		ledManager->update();
		pinManager.update();

		BeginDrawing();

		ClearBackground(BEIGE);

		DrawTexture(texturebk, 0, 0, WHITE);
		//DrawTextureEx(texture, Vector2{ 30,20 }, 0.0f, 1.0f, WHITE);
		DrawText(appName.c_str(), 590, 20, 20, BROWN);
		//DrawText("© 2017 - Mutiny Media", 30, 690, 20, BLACK);
		
		screenManager->draw();
		ledManager->draw();
		pinManager.draw();

		/*DrawTextEx(test2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", Vector2{ 102,158 }, 48, 0, BLACK);
		DrawTextEx(test, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", Vector2{100,100}, 79,0,WHITE);
		DrawTextEx(test2, "players", Vector2{ 102,258}, 48, 0, BLACK);
		DrawTextEx(test, "players", Vector2{ 100,200 }, 79, 0, WHITE);*/

		EndDrawing();

		
	}

	ledManager->close();
	

	UnloadTexture(texture);
	CloseWindow();
	CloseAudioDevice();

	
	delete ledScreen;

	return 0;
}