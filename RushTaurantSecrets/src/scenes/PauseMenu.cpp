#include "PauseMenu.h"

#include "../utils/checkML.h"

void PauseMenu::mMenu(SceneManager* sceneManager) {
	sceneManager->ChangeScene(SceneManager::MAINMENU);
}

void PauseMenu::bResume(SceneManager* sceneManager) {
	sceneManager->ChangeScene(SceneManager::RESTAURANT);
}

PauseMenu::PauseMenu(SceneManager* sceneManager) {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = new Texture(sdlutils().renderer(), "./assets/mainMenuTemp.png");
	new Image(bg, image);

	buttonResume = new GameObject(this);
	new Button(buttonResume, Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 2 * SDLUtils::instance()->height() / 5), sceneManager, bResume);
	buttonMainMenu = new GameObject(this);
	new Button(buttonMainMenu, Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 3 * SDLUtils::instance()->height() / 5), sceneManager, mMenu);
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

