#pragma once
#include "../../Structure/Scene.h"
#include "../../Utilities/Texture.h"
#include "../../GameObjects/ButtonGO.h"

class OptionsMenu : public Scene
{
private:
	const int MUSIC_VOL = 30;

	const int NUM_BUTTON = 4;
	int button;

	GameObject* bg;
	ButtonGO* buttonReturn;
	Texture* image;

	GameObject* sliderBar;
	ButtonGO* sliderButton;
	Image* sliderBarImage;
	//Image* sliderButtonImage;

	SDLUtils* sdl;
	Music* supermarketMusic;
public:
	OptionsMenu();
	~OptionsMenu();

	void handleEvents();
	void selectedButton(int selected);

	void createSlider();
	void SliderHandleEvents();
};

