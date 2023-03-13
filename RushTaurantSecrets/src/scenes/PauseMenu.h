#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/Texture.h"
#include "../gameObjects/ButtonGO.h"


class PauseMenu : public Scene
{
private:
	static void mMenu();
	static void bResume();

	GameObject* bg;
	ButtonGO* buttonResume;
	ButtonGO* buttonMainMenu;
	ButtonGO* buttonOptions;
	Texture* image;
public:
	PauseMenu();
	~PauseMenu();

	void handleEvents();
};

