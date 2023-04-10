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

	GameObject* background;
	Texture* image;
	SDLUtils* sdl;
	uint8_t menuSize;
	uint8_t spriteSize;
	DailyMenu* dailyMenu1;
	DailyMenu* dailyMenu2;
	void buttonPress();


public:
	DailyMenuScene(uint8_t msize = 4);
	void init();
	void reset();
};

