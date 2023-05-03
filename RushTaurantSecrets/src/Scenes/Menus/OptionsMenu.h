#pragma once
#include "../../Structure/Scene.h"
#include "../../Utilities/Texture.h"
#include "../../GameObjects/ButtonGO.h"
#include "../../Structure/GameManager.h"

class OptionsMenu : public Scene
{
private:
	const int MUSIC_VOL = GameManager::instance()->getMasterVolume();

	const int NUM_BUTTON = 4;
	int button;

	bool slider = false;
	bool fullscreen = false;

	GameObject* bg;
	ButtonGO* buttonReturn;
	ButtonGO* buttonControls;
	Texture* image;

	GameObject* sliderBar;
	ButtonGO* sliderButton;
	Image* sliderBarImage;

	ButtonGO* fullscreenButton;

	SDLUtils* sdl;
	Music* supermarketMusic;
public:
	OptionsMenu();
	~OptionsMenu();

	void handleEvents();
	void update();
	void selectedButton(int selected);

	void createSlider();
	void SliderHandleEvents();
	void updateCheckBox();
};

