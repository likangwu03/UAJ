#pragma once

#include "GameManager.h"

#include "../Managers/Reputation.h"
#include "../Managers/Money.h"
#include "../Managers/DayManager.h"

#include "Scene.h"
#include "../Scenes/BeforeDayStartScene.h"
#include "../Scenes/MainMenu.h"
#include "../Scenes/Restaurant.h"
#include "../Scenes/UIRestaurant.h"
#include "../Scenes/Pantry.h"
#include "../Scenes/DailyMenuScene.h"
#include "../Scenes/SuperMarket.h"
#include "../Scenes/PauseMenu.h"
#include "../Scenes/OptionsMenu.h"

#include "../Utilities/checkML.h" 

GameManager::GameManager() : reputation(nullptr), days(nullptr), money(nullptr), pantry(nullptr), pauseMenu(nullptr), supermarket(nullptr), restaurant(nullptr),
	mainMenu(nullptr), dailyMenu(nullptr), beforeDayStartScene(nullptr), currentScene(nullptr), previousScene(nullptr),
	menu(nullptr), kitchenIsland(nullptr), hasKilled(false), dayTime(0), mapsCreated(false), uiRestaurant(nullptr), killedNum(0) { };


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
	optionsMenu = new OptionsMenu();
	supermarket = new SuperMarket();
	restaurant = new Restaurant();

	try {
		days = new DayManager();
	} catch(std::exception e) { std::cout << e.what(); }

	beforeDayStartScene = new BeforeDayStartScene();

	pantry->callAfterCreating();
	restaurant->callAfterCreating();
	supermarket->callAfterCreating();


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
	delete optionsMenu;
	delete dailyMenu;
	delete beforeDayStartScene;

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
OptionsMenu* GameManager::getOptionsMenu() { return optionsMenu; }

vector<_ecs::DishInfo>* GameManager::getTodaysMenu() { return menu; }
void GameManager::setTodaysMenu(vector<_ecs::DishInfo>* tmenu) { menu = tmenu; }

void GameManager::setKichenIsland(KitchenIslandComp* KIComp) {
	kitchenIsland = KIComp;
}

void GameManager::setIngredients(vector<pair<_ecs::_ingredients_id, int>> ing) {
	if (hasKilled) {
		ing.push_back({ _ecs::MEAT,killedNum });
		killedNum = 0;
	}
	kitchenIsland->setIngredients(ing);
}

bool GameManager::getHasKill() { return hasKilled; }
void GameManager::killed() { ++killedNum; }
void GameManager::setHasKill(bool hKill) { hasKilled = hKill; }
