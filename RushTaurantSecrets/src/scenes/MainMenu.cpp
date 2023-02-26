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
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = new Texture(sdlutils().renderer(), "./assets/mainMenuTemp.png");
	new Image(bg, image);

	button = new GameObject(this);
	new Button(button, Vector((1280 / 2) - (192 * 2 / 2), 400), sceneManager, start);
}

MainMenu::~MainMenu() {
	delete image;
}

void MainMenu::handleEvents(){
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