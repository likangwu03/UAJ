#include "PauseMenu.h"
#include "../../Structure/GameManager.h"
#include "MainMenu.h"
#include "OptionsMenu.h"

#include "../../Utilities/checkML.h"

void PauseMenu::mMenu() {
	GameManager::get()->changeScene(GameManager::get()->getMainMenu());
}

void PauseMenu::bResume() {
	GameManager::get()->popScene();
}

void PauseMenu::oMenu() {
	GameManager::get()->changeScene(GameManager::get()->getOptionsMenu());
}

PauseMenu::PauseMenu() : sdl(SDLUtils::instance()), supermarketMusic(&sdl->musics().at("SUPERMARKET_MUSIC")) {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = new Texture(sdlutils().renderer(), "assets/pauseMenuTemp.png");
	new Image(bg, image);

	button = 0;
	buttonResume = new ButtonGO(this, "RESUME_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 1.8 * SDLUtils::instance()->height() / 5), 385, 130, bResume);
	buttonResume->getComponent<ButtonComp>()->setHighlighted(true);
	buttonMainMenu = new ButtonGO(this, "MAINM_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 2.8 * SDLUtils::instance()->height() / 5), 385, 130, mMenu);
	buttonOptions = new ButtonGO(this, "OPTIONS_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 3.8 * SDLUtils::instance()->height() / 5), 385, 130, oMenu);

	supermarketMusic->setMusicVolume(MUSIC_VOL);
}

PauseMenu::~PauseMenu() {
	delete image;
}

void PauseMenu::handleEvents() {
	if (ih->isKeyDown(SDLK_p)) bResume();
	Scene::handleEvents();

	if (ih->joysticksInitialised()) {
		ih->refresh();
		if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_UP)
			|| ih->getHatState(UP)) {
			button = (button - 1) % NUM_BUTTON;
			if (button < 0)
				button = button + NUM_BUTTON;
			selectedButton(button);
		}
		else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN)
			|| ih->getHatState(DOWN)) {
			button = (button + 1) % NUM_BUTTON;
			selectedButton(button);
		}
	}
	else {
		if (ih->isKeyDown(SDL_SCANCODE_W)) {
			button = (button - 1) % NUM_BUTTON;
			if (button < 0)
				button = button + NUM_BUTTON;
			selectedButton(button);
		}
		else if (ih->isKeyDown(SDL_SCANCODE_S)) {
			button = (button + 1) % NUM_BUTTON;
			selectedButton(button);
		}
	}
}

void PauseMenu::selectedButton(int selected) {
	buttonResume->getComponent<ButtonComp>()->setHighlighted(false);
	buttonMainMenu->getComponent<ButtonComp>()->setHighlighted(false);
	buttonOptions->getComponent<ButtonComp>()->setHighlighted(false);
	switch (selected)
	{
	case 0:
		buttonResume->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	case 1:
		buttonMainMenu->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	case 2:
		buttonOptions->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	}
}

