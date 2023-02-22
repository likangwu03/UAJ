#include "MainMenu.h"
#include "../structure/SceneManager.h"
#include "../scenes/Restaurant.h"
#include "../components/Button.h"
#include "../components/Transform.h"
#include "../components/Image.h"

#include "../utils/checkML.h"

void MainMenu::start(SceneManager* sceneManager) {
	sceneManager->ChangeScene(SceneManager::RESTAURANT);
}

MainMenu::MainMenu(SceneManager* sceneManager){
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, 1280, 720);
	new Image(bg, new Texture(sdlutils().renderer(), "./assets/mainMenuTemp.png"));

	button = new GameObject(this);
	new Button(button, sceneManager, start);
}

void MainMenu::handleEvents(){
	if (ih->isKeyDown(SDLK_1)) {
		SceneManager::instance()->ChangeScene(SceneManager::RESTAURANT);
	}
	else if (ih->isKeyDown(SDLK_2)) {
		SceneManager::instance()->ChangeScene(SceneManager::SUPERMARKET);
	}
	else {
		Scene::handleEvents();

	}
}