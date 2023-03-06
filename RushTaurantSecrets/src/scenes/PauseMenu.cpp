#include "PauseMenu.h"

#include "../utils/checkML.h"

void PauseMenu::mMenu() {
	SceneManager::instance()->changeScene(nullptr,2);
}

void PauseMenu::bResume() {
	SceneManager::instance()->changeScene(nullptr,1);
}

PauseMenu::PauseMenu() {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = new Texture(sdlutils().renderer(), "assets/pauseMenuTemp.png");
	new Image(bg, image);

	buttonResume = new ButtonGO(this, "RESUME_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 2 * SDLUtils::instance()->height() / 5), 385, 130, bResume);
	buttonMainMenu = new ButtonGO(this, "MAINM_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 3 * SDLUtils::instance()->height() / 5), 385, 130, mMenu);
}

PauseMenu::~PauseMenu() {
	delete image;
}

void PauseMenu::handleEvents() {
	if (ih->isKeyDown(SDLK_1)) {
		SceneManager::instance()->changeScene(new DailyMenuScene());
	}
	else if (ih->isKeyDown(SDLK_2)) {
		SceneManager::instance()->changeScene(new SuperMarket());
	}
	else {
		Scene::handleEvents();
	}
}

