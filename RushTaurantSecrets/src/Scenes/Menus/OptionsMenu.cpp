#include "OptionsMenu.h"
#include "../../Structure/GameManager.h"

#include "../../Utilities/checkML.h"


OptionsMenu::OptionsMenu() : sdl(SDLUtils::instance()), supermarketMusic(&sdl->musics().at("SUPERMARKET_MUSIC")) {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = &(sdlutils().images().at("OPTIONS_BG"));
	new Image(bg, image);

	createSlider();

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

	sliderButton = new ButtonGO(this, "SLIDER_BUTTON", "SLIDER_HIGHLIGHT",
		Vector(200, 240), 100, 100,
		[&]() {
			if ((ih->isKeyDown(SDLK_SPACE) && !slider)) slider = true;
			else if ((ih->isKeyDown(SDLK_SPACE) && slider)) slider = false;
		});

	fullscreenButton = new ButtonGO(this, "CHECKBOX", "CHECKBOX_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() - 300), 240), 100, 100,
		[&]() {
			sdl->toggleFullScreen();
		});

	button = 3;
}

OptionsMenu::~OptionsMenu() { }

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
				button = 3;
				selectedButton(button);
			}
			else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_UP)
				|| ih->getHatState(UP)) {
				button = 0;
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
				button = 3;
				selectedButton(button);
			}
			else if (ih->isKeyDown(SDLK_UP)) {
				button = 0;
				selectedButton(button);
			}
		}
	}
	else {
		SliderHandleEvents();
	}
}

void OptionsMenu::update() {
	updateCheckBox();
}

void OptionsMenu::selectedButton(int selected) {
	sliderButton->getComponent<ButtonComp>()->setHighlighted(false);
	buttonReturn->getComponent<ButtonComp>()->setHighlighted(false);
	fullscreenButton->getComponent<ButtonComp>()->setHighlighted(false);
	buttonControls->getComponent<ButtonComp>()->setHighlighted(false);
	switch (selected)
	{
	case 0:
		sliderButton->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	case 1:
		buttonControls->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	case 2:
		fullscreenButton->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	case 3:
		buttonReturn->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	}
}

void OptionsMenu::createSlider() {
	sliderBar = new GameObject(this);
	new Transform(sliderBar, { 100,250 }, { 0,0 }, 300, 80);
	sliderBarImage = new Image(sliderBar, &((*SDLUtils::instance()).images().at("SLIDER_BAR")));
}

void OptionsMenu::SliderHandleEvents(){
	int offset = 10;
	auto t = sliderButton->getComponent<Transform>();
	auto tSliderBar = sliderBar->getComponent<Transform>();
	if (ih->isKeyDown(SDLK_LEFT)) {
		if (t->getPos().getX() - offset > (tSliderBar->getPos().getX() - t->getW() / 2)) {
			t->setPos(Vector(t->getPos().getX() - offset, t->getPos().getY()));
			sliderButton->getComponent<ButtonComp>()->moveHighlighted();
			GameManager::instance()->setMasterVolume(((t->getPos().getX() + t->getW() / 2  - tSliderBar->getPos().getX()) * 100) / tSliderBar->getW());
			if(!(t->getPos().getX() - offset > (tSliderBar->getPos().getX() - t->getW() / 2)))
				GameManager::instance()->setMasterVolume(0);
		}
	}
	else if (ih->isKeyDown(SDLK_RIGHT)) {
		if (t->getPos().getX() + offset < (tSliderBar->getPos().getX() + tSliderBar->getW() - t->getW()/2)) {
			t->setPos(Vector(t->getPos().getX() + offset, t->getPos().getY()));
			sliderButton->getComponent<ButtonComp>()->moveHighlighted();
			GameManager::instance()->setMasterVolume(((t->getPos().getX() + t->getW() / 2 - tSliderBar->getPos().getX()) * 100) / tSliderBar->getW());
		}
	}
	
	supermarketMusic->setMusicVolume(GameManager::instance()->getMasterVolume());
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
