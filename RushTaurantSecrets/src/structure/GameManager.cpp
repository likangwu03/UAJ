#pragma once

#include "GameManager.h"

#include "../objects/Reputation.h"
#include "../objects/Money.h"

#include "../structure/Scene.h"
#include "../scenes/MainMenu.h"
#include "../scenes/Restaurant.h"
#include "../scenes/Pantry.h"
#include "../scenes/DailyMenuScene.h"
#include "../scenes/SuperMarket.h"
#include "../scenes/PauseMenu.h"
#include "../gameObjects/Player.h"

#include "../utils/checkML.h"

GameManager::GameManager() { };

void GameManager::initialize() {
	reputation = new Reputation();
	money = new Money();

	mainMenu = new MainMenu();
	
	sdlutils().setResizeFactor(PANTRYSIZE);
	pantry = new Pantry();
	dailyMenu = new DailyMenuScene();

	sdlutils().setResizeFactor(RESTSUPERSIZE);
	supermarket = new SuperMarket();
	pauseMenu = new PauseMenu();
	restaurant = new Restaurant();

	
	restaurant->callAfterCreating();
	supermarket->callAfterCreating();

	currentScene = mainMenu;
	previousScene = nullptr;

	hasKilled = false;
	gameOver = false;
	dayTime = false;

	restaurant->linkPantry(pantry);
	pantry->linkRestaurant(restaurant);

}

GameManager::~GameManager() {
	delete mainMenu;
	delete restaurant;
	delete pantry;
	delete supermarket;
	delete pauseMenu;
	delete dailyMenu;

	delete reputation;
	delete money;
}


void GameManager::update() {
	currentScene->update();
}
void GameManager::render() {
	currentScene->render();
}
void GameManager::handleEvents() {
	currentScene->handleEvents();
}
void GameManager::refresh() {
	currentScene->refresh();
}


void GameManager::changeScene(Scene* scene) {
	previousScene = currentScene;
	currentScene = scene;
	scene->reset();
	sdlutils().setResizeFactor(scene->getResizeFactor());
}
void GameManager::popScene() {
	if (previousScene != nullptr) {
		currentScene = previousScene;
		previousScene = nullptr;
	}
}
Scene* GameManager::getCurrentScene() { return currentScene; }
MainMenu* GameManager::getMainMenu() { return mainMenu; }
Restaurant* GameManager::getRestaurant() { return restaurant; }
Pantry* GameManager::getPantry() { return pantry; }
DailyMenuScene* GameManager::getDailyMenu() { return dailyMenu; }
SuperMarket* GameManager::getSupermarket() { return supermarket; }
PauseMenu* GameManager::getPauseMenu() { return pauseMenu; }

Reputation* GameManager::getReputation() { return reputation; }
Money* GameManager::getMoney() { return money; }

bool GameManager::getHasKill() { return hasKilled; }
void GameManager::setHasKill(bool hKill) { hasKilled = hKill; }
