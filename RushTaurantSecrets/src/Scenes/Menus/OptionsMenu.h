#pragma once
#include "../../Structure/Scene.h"
#include "../../Utilities/Texture.h"
#include "../../GameObjects/ButtonGO.h"
#include "../../Structure/GameManager.h"
#include "../../GameObjects/Slider.h"

class OptionsMenu : public Scene
{
private:

	const string FONT_PATH = "assets/Fonts/Arcadepix Plus.ttf";
	const int FONTSIZE = 50, ICONSIZE = 48, ICONX = 20, ICONY = 15, CENTEROUTLINE = 4;
	const int TARGETOFFSET = 60;

	const int NUM_BUTTON = 5;
	int button;

	bool slider = false;
	bool fullscreen = false;

	GameObject* bg;
	ButtonGO* buttonReturn;
	ButtonGO* buttonControls;
	Texture* image;

	Slider* MusicSlider;
	Slider* SoundsSlider;

	ButtonGO* sliderMusicButton;
	ButtonGO* sliderSoundsButton;

	ButtonGO* fullscreenButton;

	SDLUtils* sdl;
	Music* supermarketMusic;

	Font* font;

	Texture* MusicTexture;
	SDL_Rect MusicRect;

	Texture* SoundTexture;
	SDL_Rect SoundRect;
	
	Texture* FullScreenTexture;
	SDL_Rect FullScreenRect;

public:
	OptionsMenu();
	~OptionsMenu();

	void handleEvents();
	void update();
	void render();

	void selectedButton(int selected);

	void updateCheckBox();
	void Texts();
};

