#pragma once

#include "../Structure/Scene.h"

class GameObject;
class ButtonGO;
class Texture;

class MainMenu : public Scene {
private:
	const float BUTTONS_X = 175, BUTTONS_Y = 365,
				BUTTONS_W = 96 * 3.2, BUTTONS_H = 32 * 3.2;
	
	static void start();
	static void start2();
	static void opt();

	GameObject* bg;
	Texture* image;
	ButtonGO* oneplayer;
	ButtonGO* twoplayer;
	ButtonGO* options;
	ButtonGO* exit;

public:
	MainMenu();
	~MainMenu();

	void handleEvents();
};