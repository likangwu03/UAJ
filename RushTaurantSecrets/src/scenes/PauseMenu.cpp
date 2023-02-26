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
	image = new Texture(sdlutils().renderer(), "./assets/mainMenuTemp.png");
	new Image(bg, image);

	buttonMainMenu = new GameObject(this);
	new ButtonComp(buttonMainMenu, "MainMenu", mMenu);
	buttonResume = new GameObject(this);
	new ButtonComp(buttonResume, "Resume", bResume);
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

