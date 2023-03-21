#pragma once

#include "GameManager.h"

#include "../objects/Reputation.h"
#include "../objects/Money.h"
#include "../objects/DayManager.h"

#include "../structure/Scene.h"
#include "../scenes/BeforeDayStartScene.h"
#include "../scenes/MainMenu.h"
#include "../scenes/Restaurant.h"
#include "../scenes/UIRestaurant.h"
#include "../scenes/Pantry.h"
#include "../scenes/DailyMenuScene.h"
#include "../scenes/SuperMarket.h"
#include "../scenes/PauseMenu.h"

#include "../utils/checkML.h"

GameManager::GameManager() : reputation(nullptr), money(nullptr), pantry(nullptr), pauseMenu(nullptr), supermarket(nullptr), restaurant(nullptr),
	mainMenu(nullptr), dailyMenu(nullptr), beforeDayStartScene(nullptr), currentScene(nullptr), previousScene(nullptr),
	menu(nullptr), kitchenIsland(nullptr), hasKilled(false), dayTime(0), mapsCreated(false), uiRestaurant(nullptr), days(nullptr) { };


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

	try {
		days = new DayManager();
	} catch(std::exception e) { std::cout << e.what(); }

	//beforeDayStartScene = new BeforeDayStartScene();


	pantry->createMap();
	restaurant->callAfterCreating();
	supermarket->callAfterCreating();

	restaurant->linkPantry(pantry);
	pantry->linkRestaurant(restaurant);

	currentScene = nullptr;
	previousScene = nullptr;

	hasKilled = false;
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
	delete days;
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
void GameManager::setGameOver(int type) {
	//gameOverScene->setGameOver(type);
	//changeScene(gameOverScene);
}
Scene* GameManager::getCurrentScene() { return currentScene; }
MainMenu* GameManager::getMainMenu() { return mainMenu; }
Restaurant* GameManager::getRestaurant() { return restaurant; }
Pantry* GameManager::getPantry() { return pantry; }
DailyMenuScene* GameManager::getDailyMenu() { return dailyMenu; }
SuperMarket* GameManager::getSupermarket() { return supermarket; }
PauseMenu* GameManager::getPauseMenu() { return pauseMenu; }
BeforeDayStartScene* GameManager::getBeforeDayStart() { return beforeDayStartScene; }
Reputation* GameManager::getReputation() { return reputation; }
Money* GameManager::getMoney() { return money; }
DayManager* GameManager::getDayManager() { return days; }

vector<_ecs::DishInfo>* GameManager::getTodaysMenu() { return menu; }
void GameManager::setTodaysMenu(vector<_ecs::DishInfo>* tmenu) { menu = tmenu; }

void GameManager::setKichenIsland(KitchenIslandComp* KIComp) {
	kitchenIsland = KIComp;
}

void GameManager::setIngredients(vector<pair<_ecs::_ingredients_id, int>> ing) {
	kitchenIsland->setIngredients(ing);
}

bool GameManager::getHasKill() { return hasKilled; }
void GameManager::setHasKill(bool hKill) { hasKilled = hKill; }
