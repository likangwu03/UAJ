#pragma once
#include "../../Structure/Scene.h"
#include "../../Utilities/Texture.h"
#include "../../GameObjects/ButtonGO.h"

class OptionsMenu : public Scene
{
private:
	const int MUSIC_VOL = 30;

	GameObject* bg;
	ButtonGO* buttonReturn;
	Texture* image;

	SDLUtils* sdl;
	Music* supermarketMusic;
public:
	OptionsMenu();
	~OptionsMenu();

};

