#include "PauseMenu.h"
#include "../../Structure/GameManager.h"
#include "MainMenu.h"
#include "OptionsMenu.h"

#include "../../Utilities/checkML.h"

PauseMenu::PauseMenu() : sdl(SDLUtils::instance()), supermarketMusic(&sdl->musics().at("SUPERMARKET_MUSIC")) {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = &(sdlutils().images().at("CONTINUE_BG"));
	new Image(bg, image);

	button = 0;
	buttonResume = new ButtonGO(this, "RESUME_BUTTON_UP", "BUTTON_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() / 4 - 130 / 2), 385, 130,
		[&]() {
			GameManager::get()->popScene();
		});
	buttonResume->getComponent<ButtonComp>()->setHighlighted(true);
	buttonMainMenu = new ButtonGO(this, "MAINM_BUTTON_UP", "BUTTON_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height()*2 / 4 - 130 / 2), 385, 130,
		[&]() {
			GameManager::get()->changeScene(GameManager::get()->getScene(sc_MAINMENU));
		});
	buttonOptions = new ButtonGO(this, "OPTIONS_BUTTON", "BUTTON_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height()*3 / 4 - 130 / 2), 385, 130,
		[&]() {
			GameManager::get()->pushScene(GameManager::get()->getScene(sc_OPTIONSMENU));
		});

	supermarketMusic->setMusicVolume(MUSIC_VOL);
}

PauseMenu::~PauseMenu() {
}

void PauseMenu::handleEvents() {
	if (ih->isKeyDown(SDLK_p)) 	GameManager::get()->popScene();

	Scene::handleEvents();

	if (ih->joysticksInitialised()) {
		ih->refresh();
		if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_UP)
			|| ih->getHatState(UP) || (ih->yvalue(0, 1) < 0)) {
			button = (button - 1) % NUM_BUTTON;
			if (button < 0)
				button = button + NUM_BUTTON;
			selectedButton(button);
		}
		else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN)
			|| ih->getHatState(DOWN) || (ih->yvalue(0, 1) > 0)) {
			button = (button + 1) % NUM_BUTTON;
			selectedButton(button);
		}
	}
	else {
		if (ih->isKeyDown(SDLK_UP) || ih->isKeyDown(SDLK_w)) {
			button = (button - 1) % NUM_BUTTON;
			if (button < 0)
				button = button + NUM_BUTTON;
			selectedButton(button);
		}
		else if (ih->isKeyDown(SDLK_DOWN) || ih->isKeyDown(SDLK_s)) {
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

