#pragma once
#include "../../Utilities/SDLUtils.h"
#include "../../Structure/Component.h"
#include "../../Structure/Scene.h"
#include "../../Definitions/Structure_def.h"
#include "../../Structure/GameObject.h"
#include "../../GameObjects/DailyMenu.h"

using namespace std;

class GameObject;

class DailyMenuScene : public Scene {
	const int DISTANCE = 20, POS_Y = 30;

	const int NUM_BUTTON = 2;
	int button;

	const int MUSIC_VOL = 30;
	GameObject* background;
	Texture* image;
	SDLUtils* sdl;
	uint8_t menuSize;
	uint8_t spriteSize;
	DailyMenu* dailyMenu1;
	DailyMenu* dailyMenu2;

	Music* supermarketMusic;

public:
	void buttonPress(int menu);
	DailyMenuScene(uint8_t msize = 4);
	void init();
	void reset();

	void handleEvents();
	void render()override;
	void selectedButton(int selected);

	void initCoopMode(bool server)override;
	void quitCoopMode()override;
	virtual void receive(const Message& message);

	void setMenus(const vector<uint8_t>& menu1,const vector<uint8_t>& menu2);

	void getMenus(vector<uint8_t>& menu1, vector<uint8_t>& menu2);
};

