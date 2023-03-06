#pragma once
#include "../structure/Scene.h"
#include "../gameObjects/ButtonGO.h"
#include "../sdlutils/Texture.h"
class MainMenu : public Scene {
private:
	static void start();

	GameObject* bg;
	ButtonGO* button;
	Texture* image;

public:
	MainMenu();
	~MainMenu();

	void handleEvents() override;
};