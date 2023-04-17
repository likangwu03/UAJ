#pragma once
#include "../../Structure/Scene.h"
#include "../../Utilities/Texture.h"
#include "../../GameObjects/ButtonGO.h"

class OptionsMenu : public Scene
{
private:
	const int MUSIC_VOL = 30;

	static void mMenu();
	static void bResume();

	GameObject* bg;
	ButtonGO* buttonResume;
	Texture* image;

	SDLUtils* sdl;
	Music* supermarketMusic;
public:
	OptionsMenu();
	~OptionsMenu();

	void handleEvents();

};

