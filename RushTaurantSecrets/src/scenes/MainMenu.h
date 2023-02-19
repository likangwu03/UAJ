#pragma once
#include "../structure/Scene.h"
#include "../components/Button.h"
#include "../sdlutils/Texture.h"
class MainMenu : public Scene {
private:
	static void start(SceneManager* sceneManager);

	GameObject* bg;
	GameObject* button;

public:
	MainMenu(SceneManager* sceneManager);
};