#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/Texture.h"
#include "../structure/SceneManager.h"
#include "../components/ButtonComp.h"

class PauseMenu : public Scene
{
private:
	static void mMenu();
	static void bResume();

	GameObject* bg;
	GameObject* buttonMainMenu;
	GameObject* buttonResume;
	Texture* image;
public:
	PauseMenu(SceneManager* sceneManager);
	~PauseMenu();

	void handleEvents();
};

