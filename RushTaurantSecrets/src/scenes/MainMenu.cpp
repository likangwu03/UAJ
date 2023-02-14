#include "MainMenu.h"
#include "../structure/SceneManager.h"

void MainMenu::handleEvents() {
	if (ih->isKeyDown(SDLK_SPACE)) {
		SceneManager::instance()->ChangeScene(SceneManager::RESTAURANT);
	}
	else {
		Scene::handleEvents();
	}
}