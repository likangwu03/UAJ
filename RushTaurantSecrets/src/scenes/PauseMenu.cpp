#include "PauseMenu.h"
#include "../structure/GameManager.h"
#include "../scenes/MainMenu.h"
#include "../scenes/OptionsMenu.h"

#include "../utils/checkML.h"

void PauseMenu::mMenu() {
	GameManager::get()->changeScene(GameManager::get()->getMainMenu());
}

void PauseMenu::bResume() {
	GameManager::get()->popScene();
}

void PauseMenu::oMenu() {
	GameManager::get()->changeScene(GameManager::get()->getOptionsMenu());
}

PauseMenu::PauseMenu() {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = new Texture(sdlutils().renderer(), "assets/pauseMenuTemp.png");
	new Image(bg, image);

	buttonResume = new ButtonGO(this, "RESUME_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 1.8 * SDLUtils::instance()->height() / 5), 385, 130, bResume);
	buttonMainMenu = new ButtonGO(this, "MAINM_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 2.8 * SDLUtils::instance()->height() / 5), 385, 130, mMenu);
	buttonOptions = new ButtonGO(this, "OPTIONS_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 3.8 * SDLUtils::instance()->height() / 5), 385, 130, oMenu);
}

PauseMenu::~PauseMenu() {
	delete image;
}

void PauseMenu::handleEvents() {
	if (ih->isKeyDown(SDLK_1)) {
		GameManager::get()->changeScene((Scene*)GameManager::get()->getDailyMenu());
	}
	else if (ih->isKeyDown(SDLK_2)) {
		GameManager::get()->changeScene((Scene*)GameManager::get()->getSupermarket());
	}
	else {
		Scene::handleEvents();
	}
}

