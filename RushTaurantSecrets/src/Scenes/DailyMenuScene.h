#pragma once
#include "../Utilities/SDLUtils.h"
#include "../Structure/Component.h"
#include "../Structure/Scene.h"
#include "../Definitions/Structure_def.h"
#include "../Structure/GameObject.h"
#include "../GameObjects/DailyMenu.h"

using namespace std;

class GameObject;

class DailyMenuScene : public Scene {
	const int DISTANCE = 20, POS_Y = 30;

	SDLUtils* sdl;
	uint8_t menuSize;
	uint8_t spriteSize;
	static void select1();
	static void select2();
	DailyMenu* dailyMenu1;
	DailyMenu* dailyMenu2;
	bool changeMenu;

public:
	DailyMenuScene(uint8_t msize = 4);
	void init();
	void update();
	void reset();
};

