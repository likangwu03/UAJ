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
#include "../Scenes/EndOfDayScene.h"
#include "../Scenes/GameOverScene.h"
#include "../Scenes/ContinueMenu.h"
#include "../Scenes/PantryUI.h"
#include "../Scenes/IntroScene.h"
#include "../Scenes/FirstDayAfterKillScene.h"
#include "../Scenes/SecondDayAfterKillScene.h"
#include <sstream>
#include <fstream>
#include "../Utilities/JSON.h"
#include "../Utilities/Texture.h"
#include "../Utilities/checkML.h" 

GameManager::GameManager() : reputation(nullptr), days(nullptr), money(nullptr), pantry(nullptr), pauseMenu(nullptr), supermarket(nullptr), restaurant(nullptr),
	mainMenu(nullptr), dailyMenu(nullptr), beforeDayStartScene(nullptr), currentScene(nullptr), previousScene(nullptr),optionsMenu(nullptr),gameOverScene(nullptr),
	continueMenu(nullptr),menu(nullptr), kitchenIsland(nullptr), twoPlayers(false),
	hasKilled(false), dayTime(0), mapsCreated(false), uiRestaurant(nullptr), endScene(nullptr), killedNum(0),hasEverKilled({false,0}) { };


void GameManager::initialize() {
	reputation = new Reputation();
	money = new Money();
	//menu = new vector<_ecs::_dish_id>();

	
	mainMenu = new MainMenu();
	dailyMenu = new DailyMenuScene();
	gameOverScene = new GameOverScene();
	

	sdlutils().setResizeFactor(PANTRYSIZE);
	pantryUI = new PantryUI();
	pantry = new Pantry(pantryUI);

	sdlutils().setResizeFactor(RESTSUPERSIZE);
	pauseMenu = new PauseMenu();
	optionsMenu = new OptionsMenu();
	continueMenu = new ContinueMenu();
	supermarket = new SuperMarket();
	restaurant = new Restaurant();

	try {
		days = new DayManager();
		days->nextDay();
	} catch(std::exception e) { std::cout << e.what(); }

	beforeDayStartScene = new BeforeDayStartScene();
	endScene = new EndOfDayScene();

	introScene = new IntroScene();
	firstDayAfterKillScene = new FirstDayAfterKillScene();
	secondDayAfterKillScene = new SecondDayAfterKillScene();

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
	delete gameOverScene;
	delete continueMenu;
	delete endScene;
	delete pantryUI;
	delete introScene;
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
	sdlutils().setResizeFactor(scene->getResizeFactor());


}
void GameManager::popScene() {
	if (previousScene != nullptr) {
		currentScene = previousScene;
		previousScene = nullptr;
		sdlutils().setResizeFactor(currentScene->getResizeFactor());
	}
}
void GameManager::deleteCurrentScene() {
	if (previousScene != nullptr) {
		delete currentScene;
		currentScene = previousScene;
		previousScene = nullptr;
		sdlutils().setResizeFactor(currentScene->getResizeFactor());
	}
}

void GameManager::skipfromTransition() {
		delete currentScene;
		currentScene = previousScene;
		previousScene->finishScene();
}


void GameManager::setGameOver(int type) {
	gameOverScene->setGameOver(endingType(type));
	changeScene(gameOverScene);
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
ContinueMenu* GameManager:: getContinueMenu() { return continueMenu; }
EndOfDayScene* GameManager::getEndOfDay() { return endScene; }
IntroScene* GameManager::getIntroScene() { return introScene; }
FirstDayAfterKillScene* GameManager::getFirstDayAfterKillScene() { return firstDayAfterKillScene; }
SecondDayAfterKillScene* GameManager::getSecondDayAfterKillScene() { return secondDayAfterKillScene; }

vector<_ecs::DishInfo>* GameManager::getTodaysMenu() { return menu; }
void GameManager::setTodaysMenu(vector<_ecs::DishInfo>* tmenu) { menu = tmenu; }


void GameManager::setKichenIsland(KitchenIslandComp* KIComp) {
	kitchenIsland = KIComp;
}

void GameManager::setIngredients(vector<pair<_ecs::_ingredients_id, int>> ing) {
	if (hasKilled) {
		ing.push_back({ _ecs::MEAT,killedNum });
		killedNum = 0;
		hasKilled = false;
	}
	kitchenIsland->setIngredients(ing);
}

pair<bool,int> GameManager::getHasEverKilled() { return hasEverKilled; }

bool GameManager::getHasKill() { return hasKilled; }
void GameManager::killed() { ++killedNum; }
void GameManager::setHasKill(bool hKill) { hasKilled = hKill; if (!hasEverKilled.first) hasEverKilled={ true,days->getDay() }; }


void GameManager::save() {
	//crear y abrir fichero
	stringstream file;
	file << "assets/savegame" << twoPlayers << ".rsdat";
	ofstream write(file.str());

	// información
	write << days->getDay() << endl;//n dia
	write << money->getMoney() << endl;
	write << reputation->getReputation() << endl;
	write << hasKilled << endl;
	write << killedNum << endl;

	// Close the file
	write.close();
}

void GameManager::load() {
	ifstream load;
	int aux;
	stringstream file;
	file << "assets/savegame" << twoPlayers << ".rsdat";
	load.open(file.str());
	if (!load.is_open()) {}
	load >> aux;
	days->setDay(aux);

	load >> aux;
	money->addMoney(aux - money->getMoney());
	load >> aux;
	reputation->addReputatiton(aux - reputation->getReputation());
	load >> aux;
	hasKilled = aux;
	load >> killedNum;
	load.close();
}

bool GameManager::checkload() {
	stringstream file;
	file << "assets/savegame" << twoPlayers << ".rsdat";
	ifstream load;
	load.open(file.str());
	bool aux = load.is_open();
	int d;
	if (aux) {
		load >> d;
	}
	load.close();
	return aux&&d!=1;
}

void GameManager::newGame() {
	days->setDay(1);
	hasKilled = false;
	killedNum = 0;
	money->newGame();
	reputation->newGame();
	save();
}

vector<dialogueInfo> GameManager::getDialogueInfo(std::string d) {
	vector<dialogueInfo> dialogues;

	std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile("assets/Dialogues/" + d));
	if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
		throw "Something went wrong while load/parsing '" + d + "'";
	}

	JSONObject root = jValueRoot->AsObject();
	JSONValue* jValue = nullptr;

	jValue = root["dialogues"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			dialogues.reserve(jValue->AsArray().size()); // reserve enough space to avoid resizing
			for (auto& v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string chr = vObj["Character"]->AsString();
					std::string txt = vObj["Text"]->AsString();
					std::string prt = vObj["Portrait"]->AsString();
					deque<std::string> text;
					text.push_back(txt);
					dialogueInfo dInfo(chr, text, &sdlutils().images().at(prt) );

					dialogues.emplace_back(dInfo);
				}
				else {
					throw "'Dialogues' array in '" + d
						+ "' includes and invalid value";
				}
			}
		}
		else {
			throw "'Dialogues' is not an array in '" + d + "'";
		}
	}

	return dialogues;
}