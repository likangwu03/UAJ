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

GameManager::GameManager() : reputation(nullptr), money(nullptr), pantry(nullptr), pauseMenu(nullptr), supermarket(nullptr), restaurant(nullptr),
mainMenu(nullptr), dailyMenu(nullptr), currentScene(nullptr), previousScene(nullptr), hasKilled(false), gameOver(false), dayTime(false) { };


void GameManager::initialize() {
	reputation = new Reputation();
	money = new Money();
	//menu = new vector<_ecs::_dish_id>();

	
	mainMenu = new MainMenu();
	dailyMenu = new DailyMenuScene();

	sdlutils().setResizeFactor(PANTRYSIZE);
	pantry = new Pantry();

	sdlutils().setResizeFactor(RESTSUPERSIZE);
	pauseMenu = new PauseMenu();
	supermarket = new SuperMarket();
	restaurant = new Restaurant();

	

	restaurant->callAfterCreating();
	supermarket->callAfterCreating();

	restaurant->linkPantry(pantry);
	pantry->linkRestaurant(restaurant);

	currentScene = nullptr;
	previousScene = nullptr;

	hasKilled = false;
	gameOver = false;
	dayTime = false;

	changeScene(mainMenu);
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
		sdlutils().setResizeFactor(currentScene->getResizeFactor());

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

vector<_ecs::DishInfo>* GameManager::getTodaysMenu() { return menu; }
void GameManager::setTodaysMenu(vector<_ecs::DishInfo>* tmenu) { menu = tmenu; }

bool GameManager::getHasKill() { return hasKilled; }
void GameManager::setHasKill(bool hKill) { hasKilled = hKill; }
