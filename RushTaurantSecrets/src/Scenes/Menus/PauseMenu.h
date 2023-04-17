#pragma once
#include "../../Structure/Scene.h"
#include "../../Utilities/Texture.h"
#include "../../GameObjects/ButtonGO.h"

class PauseMenu : public Scene
{
private:
	// hacer global para que sea modificable
	const int MUSIC_VOL = 30;

	static void mMenu();
	static void bResume();
	static void oMenu();

	GameObject* bg;
	ButtonGO* buttonResume;
	ButtonGO* buttonMainMenu;
	ButtonGO* buttonOptions;
	Texture* image;

	SDLUtils* sdl;
	Music* supermarketMusic;
public:
	PauseMenu();
	~PauseMenu();

	void handleEvents();
};

