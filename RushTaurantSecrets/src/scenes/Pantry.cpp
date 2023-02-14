#include "Pantry.h"
#include "Restaurant.h"
#include "../structure/SceneManager.h"

void Pantry::linkRestaurant(Restaurant* rest) {
	this->rest = rest;
	//ui = rest->getUI();
}

void Pantry::render() {
	Scene::render();
	//ui->render();
}

void Pantry::update() {
	Scene::update();
	rest->Scene::update();
}

void Pantry::handleEvents() {
	if (ih->isKeyDown(SDLK_1)) {
		SceneManager::instance()->ChangeScene(SceneManager::RESTAURANT);
	}
	else if (ih->isKeyDown(SDLK_2)) {
		SceneManager::instance()->ChangeScene(SceneManager::MAINMENU);
	}
	else {
		Scene::handleEvents();
		//ui->handleEvents();
	}
}