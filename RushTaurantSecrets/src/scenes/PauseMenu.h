#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/Texture.h"
#include "../structure/SceneManager.h"
#include "../components/Button.h"

class PauseMenu : public Scene
{
private:
	static void mMenu(SceneManager* sceneManager);
	static void bResume(SceneManager* sceneManager);

	GameObject* bg;
	GameObject* buttonMainMenu;
	GameObject* buttonResume;
	Texture* image;
public:
	PauseMenu(SceneManager* sceneManager);
	~PauseMenu();

	void handleEvents();
};

