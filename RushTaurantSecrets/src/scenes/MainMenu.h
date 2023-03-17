#pragma once

#include "../structure/Scene.h"

class GameObject;
class ButtonGO;
class Texture;

class MainMenu : public Scene {
private:
	static void start();

	GameObject* bg;
	ButtonGO* oneplayer;
	ButtonGO* twoplayer;
	ButtonGO* options;
	ButtonGO* exit;
	Texture* image;

public:
	MainMenu();
	~MainMenu();

	void handleEvents();
};