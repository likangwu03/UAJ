#include "OptionsMenu.h"
#include "../../Structure/GameManager.h"

#include "../../Utilities/checkML.h"


OptionsMenu::OptionsMenu() : sdl(SDLUtils::instance()), supermarketMusic(&sdl->musics().at("SUPERMARKET_MUSIC")) {

	font = new Font(FONT_PATH, FONTSIZE);

	Texts();

	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = &(sdlutils().images().at("OPTIONS_BG"));
	new Image(bg, image);


	buttonReturn = new ButtonGO(this, "RESUME_BUTTON_UP", "BUTTON_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 3.3 * SDLUtils::instance()->height() / 5), 385, 130, 
		[&]() {
			GameManager::get()->popScene();
		});
	buttonReturn->getComponent<ButtonComp>()->setHighlighted(true);
	
	buttonControls = new ButtonGO(this, "CONTROLS_BUTTON", "BUTTON_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 1.55 * SDLUtils::instance()->height() / 5), 385, 130, 
		[&]() {
			GameManager::get()->popScene();
		});

	sliderMusicButton = new ButtonGO(this, "SLIDER_BUTTON", "SLIDER_HIGHLIGHT",
		Vector(200, 190), 100, 100,
		[&]() {
			auto sliderComp = MusicSlider->getComponent<SliderComponent>();
			slider = sliderComp->getSlider();

			if ((ih->isKeyDown(SDLK_SPACE) && !slider)) 
				sliderComp->setSlider(true);			
			else if ((ih->isKeyDown(SDLK_SPACE) && slider)) 
				sliderComp->setSlider(false);

			slider = sliderComp->getSlider();
		});

	sliderSoundsButton = new ButtonGO(this, "SLIDER_BUTTON", "SLIDER_HIGHLIGHT",
		Vector(200, 390), 100, 100,
		[&]() {
			auto sliderComp = SoundsSlider->getComponent<SliderComponent>();
			slider = sliderComp->getSlider();

			if ((ih->isKeyDown(SDLK_SPACE) && !slider))
				sliderComp->setSlider(true);
			else if ((ih->isKeyDown(SDLK_SPACE) && slider))
				sliderComp->setSlider(false);

			slider = sliderComp->getSlider();
		});

	fullscreenButton = new ButtonGO(this, "CHECKBOX", "CHECKBOX_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() - 300), 240), 100, 100,
		[&]() {
			sdl->toggleFullScreen();
		});

	MusicSlider = new Slider(this, 100, 200, sliderMusicButton);
	SoundsSlider = new Slider(this, 100, 400, sliderSoundsButton);

	button = 4;
}

OptionsMenu::~OptionsMenu() {
	delete font;
	delete MusicTexture;
	delete FullScreenTexture;
	delete SoundTexture;
}

void OptionsMenu::handleEvents() {

	Scene::handleEvents();

	if (ih->isKeyDown(SDLK_p)) 	GameManager::get()->popScene();

	if (!slider) {	
		if (ih->joysticksInitialised()) {
			ih->refresh();
			if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT)
				|| ih->getHatState(LEFT)) {
				button = (button - 1) % NUM_BUTTON;
				if (button < 0)
					button = button + NUM_BUTTON;
				selectedButton(button);
			}
			else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
				|| ih->getHatState(RIGHT)) {
				button = (button + 1) % NUM_BUTTON;
				selectedButton(button);
			}
			else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN)
				|| ih->getHatState(DOWN)) {
				if (button == 0)
					button = 1;
				else
					button = 4;
				selectedButton(button);
			}
			else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_UP)
				|| ih->getHatState(UP)) {
				if (button == 1)
					button = 0;
				else if (button == 4)
					button = 1;
				selectedButton(button);
			}
		}
		else {
			if (ih->isKeyDown(SDLK_LEFT)) {
				button = (button - 1) % NUM_BUTTON;
				if (button < 0)
					button = button + NUM_BUTTON;
				selectedButton(button);
			}
			else if (ih->isKeyDown(SDLK_RIGHT)) {
				button = (button + 1) % NUM_BUTTON;
				selectedButton(button);
			}
			else if (ih->isKeyDown(SDLK_DOWN)) {
				if (button == 0)
					button = 1;
				else 
					button = 4;
				selectedButton(button);
			}
			else if (ih->isKeyDown(SDLK_UP)) {
				if (button == 1)
					button = 0;
				else if (button == 4)
					button = 1;
				selectedButton(button);
			}
		}
	}

	supermarketMusic->setMusicVolume(GameManager::instance()->getMasterVolume());
}

void OptionsMenu::update() {
	updateCheckBox();
}

void OptionsMenu::render() {
	Scene::render();

	MusicTexture->render(MusicRect);
	SoundTexture->render(SoundRect);
	FullScreenTexture->render(FullScreenRect);
}

void OptionsMenu::selectedButton(int selected) {
	sliderMusicButton->getComponent<ButtonComp>()->setHighlighted(false);
	sliderSoundsButton->getComponent<ButtonComp>()->setHighlighted(false);
	buttonReturn->getComponent<ButtonComp>()->setHighlighted(false);
	fullscreenButton->getComponent<ButtonComp>()->setHighlighted(false);
	buttonControls->getComponent<ButtonComp>()->setHighlighted(false);
	switch (selected)
	{
	case 0:
		sliderMusicButton->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	case 1:
		sliderSoundsButton->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	case 2:
		buttonControls->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	case 3:
		fullscreenButton->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	case 4:
		buttonReturn->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	}
}

void OptionsMenu::updateCheckBox() {
	auto flag = SDL_GetWindowFlags(sdlutils().window());
	auto is_fullscreen = flag & SDL_WINDOW_FULLSCREEN;
	if (is_fullscreen == SDL_WINDOW_FULLSCREEN)
		fullscreen = true;
	else
		fullscreen = false;

	if (fullscreen)
		fullscreenButton->getComponent<Image>()->setTexture("CHECKBOX_CHECK");
	else
		fullscreenButton->getComponent<Image>()->setTexture("CHECKBOX");
}

void OptionsMenu::Texts() {
	std::string strMusic = "MUSIC";
	MusicTexture = new Texture(sdl->renderer(), strMusic, *font, build_sdlcolor(0xB68962ff));
	MusicRect = { 125, 115, 2*MusicTexture->width() ,2*MusicTexture->height() };
	std::string strSound = "SOUND";
	SoundTexture = new Texture(sdl->renderer(), strSound, *font, build_sdlcolor(0xB68962ff));
	SoundRect = { 125, 315, 2 * SoundTexture->width() ,2 * SoundTexture->height() };
	std::string strFullScreen = "FULLSCREEN";
	FullScreenTexture = new Texture(sdl->renderer(), strFullScreen, *font, build_sdlcolor(0xB68962ff));
	FullScreenRect = { 870, 160, int(1.3*FullScreenTexture->width()), int(1.3*FullScreenTexture->height()) };

}
