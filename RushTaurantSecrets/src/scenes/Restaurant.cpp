#include "Restaurant.h"
#include "Pantry.h"
#include "../structure/SceneManager.h"

void Restaurant::linkPantry(Pantry* pantry) {
	this->pantry = pantry;
}

void Restaurant::render() {
	Scene::render();
	ui->render();
}

void Restaurant::update() {
	Scene::update();
	pantry->Scene::update();
}

void Restaurant::handleEvents() {
	if (ih->isKeyDown(SDLK_1)) {
		SceneManager::instance()->ChangeScene(SceneManager::PANTRY);
	}
	else if (ih->isKeyDown(SDLK_2)) {
		SceneManager::instance()->ChangeScene(SceneManager::MAINMENU);
	}
	else {
		Scene::handleEvents();
		//ui->handleEvents();
	}
	
}