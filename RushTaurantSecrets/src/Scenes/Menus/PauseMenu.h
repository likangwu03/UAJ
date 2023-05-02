#pragma once
#include "../../Structure/Scene.h"
#include "../../Utilities/Texture.h"
#include "../../GameObjects/ButtonGO.h"

class PauseMenu : public Scene
{
private:
	// hacer global para que sea modificable
	const int MUSIC_VOL = 30;

	const int NUM_BUTTON = 3;
	int button;

	GameObject* bg;
	ButtonGO* buttonResume;
	ButtonGO* buttonMainMenu;
	ButtonGO* buttonOptions;
	Texture* image;

	SDLUtils* sdl;
	Music* supermarketMusic;
	Music* restaurantMusic;
	Music* pantryMusic;
public:
	PauseMenu();
	~PauseMenu();

	void handleEvents();
	void selectedButton(int selected);
};

