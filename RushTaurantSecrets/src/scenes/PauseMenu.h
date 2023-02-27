#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/Texture.h"
#include "../structure/SceneManager.h"
#include "../gameObjects/ButtonGO.h"


class PauseMenu : public Scene
{
private:
	static void mMenu();
	static void bResume();

	GameObject* bg;
	ButtonGO* buttonResume;
	ButtonGO* buttonMainMenu;
	Texture* image;
public:
	PauseMenu(SceneManager* sceneManager);
	~PauseMenu();

	void handleEvents();
};

