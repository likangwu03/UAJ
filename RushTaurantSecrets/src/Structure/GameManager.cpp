#pragma once

#include "GameManager.h"

#include "../Managers/Reputation.h"
#include "../Managers/Money.h"
#include "../Managers/DayManager.h"

#include "Scene.h"
#include "../Scenes/GameScenes/BeforeDayStartScene.h"
#include "../Scenes/Menus/MainMenu.h"
#include "../Scenes/GameScenes/Restaurant.h"
#include "../Scenes/GameScenes/Pantry.h"
#include "../Scenes/GameScenes/DailyMenuScene.h"
#include "../Scenes/GameScenes/SuperMarket.h"
#include "../Scenes/Menus/PauseMenu.h"
#include "../Scenes/Menus/OptionsMenu.h"
#include "../Scenes/GameScenes/EndOfDayScene.h"
#include "../Scenes/GameScenes/GameOverScene.h"
#include "../Scenes/Menus/ContinueMenu.h"
#include "../Scenes/HUD/PantryUI.h"
#include "../Scenes/Cutscenes/IntroScene.h"
#include "../Scenes/Cutscenes/FirstDayAfterKillScene.h"
#include "../Scenes/Cutscenes/SecondDayAfterKillScene.h"
#include "../Scenes/Menus/CoopMenu.h"
#include "../Scenes/TransitionScene.h"
#include <sstream>
#include <fstream>

#include "../Utilities/JSON.h"
#include "../Utilities/Texture.h"
#include "../Utilities/checkML.h" 

GameManager::GameManager() : scenes(), deleteScene(nullptr), deleteTransition(false),
	restaurant(nullptr), supermarket(nullptr), pantry(nullptr), dailyMenu(nullptr), pantryUI(nullptr),
	mainMenu(nullptr), optionsMenu(nullptr), pauseMenu(nullptr), continueMenu(nullptr), endScene(nullptr), beforeDayStartScene(nullptr), gameOverScene(nullptr), coopMenu(nullptr),
	reputation(nullptr), days(nullptr), money(nullptr),
	menu(nullptr), kitchenIsland(nullptr),
	hasKilled(false), hasEverKilled({ false,0 }), mapsCreated(false), twoPlayers(false), killedNum(0),
	introScene(nullptr), firstDayAfterKillScene(nullptr), secondDayAfterKillScene(nullptr) { };


void GameManager::initialize() {
	reputation = new Reputation();
	money = new Money();
	hasKilled = false;

	
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
	beforeDayStartScene = new BeforeDayStartScene();
	secondDayAfterKillScene = new SecondDayAfterKillScene();
	firstDayAfterKillScene = new FirstDayAfterKillScene();
	coopMenu = new CoopMenu();

	try {
		days = new DayManager();
	} catch(std::exception e) { std::cout << e.what(); }

	beforeDayStartScene->init();

	endScene = new EndOfDayScene();
	introScene = new IntroScene();

	pantry->callAfterCreating();
	restaurant->callAfterCreating();
	supermarket->callAfterCreating();
	days->nextDay();
	delete deleteScene;


	changeScene(mainMenu);

}

GameManager::~GameManager() {
	delete secondDayAfterKillScene;
	delete firstDayAfterKillScene;
	delete introScene;

	delete days;
	delete money;
	delete reputation;

	delete coopMenu;
	delete gameOverScene;
	delete beforeDayStartScene;
	delete endScene;
	delete continueMenu;
	delete pauseMenu;
	delete optionsMenu;
	delete mainMenu;
	delete pantryUI;
	delete dailyMenu;

	delete supermarket;
	delete pantry;
	delete restaurant;

	if (deleteScene != nullptr)
		delete scenes.top();
}


void GameManager::update() {
	if (!scenes.empty())
		scenes.top()->update();
}
void GameManager::render() {
	if (!scenes.empty())
		scenes.top()->render();
}
void GameManager::handleEvents() {
	if (!scenes.empty())
		scenes.top()->handleEvents();
}
void GameManager::refresh() {
	if (!scenes.empty())
		scenes.top()->refresh();

	if (deleteTransition && deleteScene != nullptr){
		deleteTransition = false;
		delete deleteScene;
		deleteScene = nullptr;
	}
}


void GameManager::changeScene(Scene* scene, bool longerTransition) {
	if (!scenes.empty())
		if (scenes.top() != scene) popScene();

	pushScene(scene);
	if (!longerTransition) {
		deleteScene = new TransitionScene(scene, TRANSITION_TIME);
		scenes.push(deleteScene);
	}
}
void GameManager::popScene(Scene* transitionScene, CinematicBaseScene* cinematic) {
	if (!scenes.empty()) {
		if (transitionScene != nullptr) {
			deleteTransition = true;
			deleteScene = transitionScene;
		}
		if (cinematic != nullptr) cinematic->transitionEnded();

		scenes.pop();
		if (!scenes.empty()) sdlutils().setResizeFactor(scenes.top()->getResizeFactor());
	}
}
void GameManager::pushScene(Scene* scene, bool longerTransition) {
	sdlutils().setResizeFactor(scene->getResizeFactor());
	scenes.push(scene);

	if(longerTransition)
		deleteScene = scene;
}
void GameManager::skipfromTransition() {
	deleteScene = scenes.top();
	popScene();
	
	scenes.top()->finishScene();
	
}

bool GameManager::canChangeScene() {
	return scenes.top() != deleteScene;
}


void GameManager::setGameOver(int type) {
	gameOverScene->setGameOver(endingType(type));
	changeScene(gameOverScene);
}


Scene* GameManager::getCurrentScene() { return scenes.top(); }
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
CoopMenu* GameManager:: getCoopMenu() { return coopMenu; }
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


void GameManager::resetScenes() {
	beforeDayStartScene->reset();
	beforeDayStartScene->nextDay();

	dailyMenu->reset();
	dailyMenu->nextDay();

	supermarket->reset();
	supermarket->nextDay();

	restaurant->reset();
	restaurant->nextDay();
	restaurant->getUI()->nextDay();

	pantry->reset();
	pantry->nextDay();
	
	endScene->reset();
	endScene->nextDay();
}

void GameManager::save() {
	//crear y abrir fichero
	stringstream file;
	file << "assets/savegame" << twoPlayers << ".rsdat";
	ofstream write(file.str());

	// información
	write << days->getDay()+1 << endl;//n dia
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

	resetScenes();
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

	resetScenes();
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