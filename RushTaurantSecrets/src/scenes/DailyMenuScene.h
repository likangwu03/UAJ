#pragma once
#include "../sdlutils/SDLUtils.h"
#include "../structure/Component.h"
#include "../structure/Scene.h"
#include "../structure/Structure_def.h"
#include "../structure/GameObject.h"
#include "../gameObjects/DailyMenu.h"

using namespace std;

class GameObject;

class DailyMenuScene : public Scene {
	const int DISTANCE = 40;

	SDLUtils* sdl;
	uint8_t menuSize;
	uint8_t spriteSize;
	static void select1();
	static void select2();
	DailyMenu* dailyMenu1;
	DailyMenu* dailyMenu2;

public:
	DailyMenuScene(uint8_t msize = 4);
	void handleEvents();
	void init();
};

