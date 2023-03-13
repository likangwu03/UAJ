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
	mainMenu = new MainMenu;
	restaurant = new Restaurant;
	pantry = new Pantry;
	dailyMenu = new DailyMenuScene;
	supermarket = new SuperMarket;
	pauseMenu = new PauseMenu;
	reputation = new Reputation;
	money = new Money;

	currentScene = mainMenu;
	previousScene = nullptr;

	hasKilled = false;
	gameOver = false;
	dayTime = false;

	pantry->linkRestaurant(restaurant);

}

GameManager::~GameManager() {
	delete mainMenu;
	delete restaurant;
	delete pantry;
	delete supermarket;
	delete pauseMenu;

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
	if (currentScene != scene) {
		previousScene = currentScene;
		currentScene = scene;
		scene->reset();
		sdlutils().setResizeFactor(scene->getResizeFactor());
	}
}
void GameManager::popScene() {
	if (previousScene != nullptr) {
		currentScene = previousScene;
		previousScene = nullptr;
	}
}
Scene* GameManager::getCurrentScene() { return currentScene; }
Scene* GameManager::getMainMenu() { return mainMenu; }
Scene* GameManager::getRestaurant() { return restaurant; }
Scene* GameManager::getPantry() { return pantry; }
Scene* GameManager::getDailyMenu() { return dailyMenu; }
Scene* GameManager::getSupermarket() { return supermarket; }
Scene* GameManager::getPauseMenu() { return pauseMenu; }

Reputation* GameManager::getReputation() { return reputation; }
Money* GameManager::getMoney() { return money; }

bool GameManager::getHasKill() { return hasKilled; }
void GameManager::setHasKill(bool hKill) { hasKilled = hKill; }
