#include "PauseMenu.h"

#include "../utils/checkML.h"

void PauseMenu::mMenu() {
	SceneManager::instance()->ChangeScene(SceneManager::MAINMENU);
}

void PauseMenu::bResume() {
	SceneManager::instance()->ChangeScene(SceneManager::RESTAURANT);
}

PauseMenu::PauseMenu(SceneManager* sceneManager) {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = new Texture(sdlutils().renderer(), "assets/pauseMenuTemp.png");
	new Image(bg, image);

	buttonResume = new ButtonGO(this, "RESUME_BUTTON_UP", "RESUME_BUTTON_DOWN",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 2 * SDLUtils::instance()->height() / 5), 385, 130, bResume);
	buttonMainMenu = new ButtonGO(this, "MAINM_BUTTON_UP", "MAINM_BUTTON_DOWN",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 3 * SDLUtils::instance()->height() / 5), 385, 130, mMenu);
}

PauseMenu::~PauseMenu() {
	delete image;
}

void PauseMenu::handleEvents() {
	if (ih->isKeyDown(SDLK_1)) {
		SceneManager::instance()->ChangeScene(SceneManager::DAILYMENU);
	}
	else if (ih->isKeyDown(SDLK_2)) {
		SceneManager::instance()->ChangeScene(SceneManager::SUPERMARKET);
	}
	else {
		Scene::handleEvents();
	}
}

