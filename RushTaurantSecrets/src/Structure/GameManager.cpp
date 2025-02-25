#pragma once

#include "GameManager.h"

#include "../Managers/Reputation.h"
#include "../Managers/Money.h"
#include "../Managers/DayManager.h"

#include "Scene.h"
#include "../Scenes/GameScenes/BeforeDayStartScene.h"
#include "../Scenes/Menus/MainMenu.h"
#include "../Scenes/GameScenes/Restaurant.h"
#include "../Scenes/HUD/UIPantry.h"
#include "../Scenes/GameScenes/Pantry.h"
#include "../Scenes/GameScenes/DailyMenuScene.h"
#include "../Scenes/GameScenes/SuperMarket.h"

#include "../Scenes/Menus/PauseMenu.h"
#include "../Scenes/Menus/OptionsMenu.h"
#include "../Scenes/GameScenes/EndOfDayScene.h"
#include "../Scenes/GameScenes/GameOverScene.h"
#include "../Scenes/Menus/ContinueMenu.h"
#include "../Scenes/Menus/CoopMenu.h"

#include "../Scenes/TransitionScene.h"
#include "../scenes/Cutscenes/Day3IntroNoKill.h"
#include "../scenes/Cutscenes/Day2IntroScene.h"
#include "../Scenes/Cutscenes/Day1IntroScene.h"
#include "../Scenes/Cutscenes/FirstDayAfterKillScene.h"
#include "../Scenes/Cutscenes/SecondDayAfterKillScene.h"
#include "../Scenes/Cutscenes/NormalEndingScene.h"
#include "../Scenes/Cutscenes/BadEnding1Scene.h"
#include "../Scenes/Cutscenes/BadEnding2Scene.h"
#include "../Scenes/Cutscenes/BadEnding3Scene.h"
#include "../Scenes/Cutscenes/BadEnding4Scene.h"
#include "../Scenes/Cutscenes/Day2EndingNoKillScene.h"
#include "../Scenes/Cutscenes/Day2EndingKillScene.h"
#include "../Scenes/Cutscenes/Day1EndingScene.h"
#include "../Scenes/Cutscenes/HappyEndingScene.h"

#include <sstream>
#include <fstream>

#include "../Utilities/JSON.h"
#include "../Utilities/Texture.h"
#include "../Utilities/checkML.h" 

#include <iostream>
#include <chrono>
#include <ctime>


GameManager::GameManager() : scenes(), allScenes(), deleteScene(nullptr), deleteTransition(false),
restaurant(nullptr), supermarket(nullptr), pantry(nullptr), reputation(nullptr), days(nullptr), money(nullptr), beforeDayStartScene(nullptr),
menu(nullptr), kitchenIsland(nullptr), hasKilled(false), hasEverKilled({ false,0 }), mapsCreated(false), twoPlayers(false), killedNum(0), gameOver(false)
{ };


void GameManager::initialize() {
	reputation = new Reputation();
	money = new Money();
	hasKilled = false;
	dailyMenu = new DailyMenuScene();

	allScenes.insert({ _ecs::sc_MAINMENU, new MainMenu() });
	allScenes.insert({ _ecs::sc_DAILYMENU, dailyMenu });
	allScenes.insert({ _ecs::sc_GAMEOVER, new GameOverScene() });
	try {
		days = new DayManager();
	}
	catch (std::exception e) { std::cout << e.what(); }

	sdlutils().setResizeFactor(PANTRYSIZE);
	UIPantry* pantryUI = new UIPantry();
	pantry = new Pantry(pantryUI);
	allScenes.insert({ _ecs::sc_PANTRY, pantry });
	pantry->initComponent();
	sdlutils().setResizeFactor(RESTSUPERSIZE);
	allScenes.insert({ _ecs::sc_PAUSEMENU, new PauseMenu() });
	allScenes.insert({ _ecs::sc_OPTIONSMENU, new OptionsMenu() });
	allScenes.insert({ _ecs::sc_CONTINUEMENU, new ContinueMenu() });
	/*beforeDayStartScene = new BeforeDayStartScene();
	allScenes.insert({ _ecs::sc_BEFOREDAYSTART, beforeDayStartScene });
	allScenes.insert({ _ecs::sc_COOPMENU, new CoopMenu() });*/

	supermarket = new SuperMarket();
	restaurant = new Restaurant();
	allScenes.insert({ _ecs::sc_SUPERMARKET, supermarket });
	allScenes.insert({ _ecs::sc_RESTAURANT, restaurant });

	/*beforeDayStartScene->init();
	allScenes.insert({ _ecs::sc_ENDOFDAY, new EndOfDayScene() });*/

	pantry->callAfterCreating();
	restaurant->callAfterCreating();
	supermarket->callAfterCreating();

	days->nextDay();

	//allScenes.insert({ _ecs::sc_INTRO1, new Day1IntroScene() });	// REVISADA 2
	//allScenes.insert({ _ecs::sc_INTRO2, new Day2IntroScene() });	// REVISADA 2
	//allScenes.insert({ _ecs::sc_INTRO3NOKILL, new Day3IntroNoKill() });	// REVISADA 2
	//allScenes.insert({ _ecs::sc_ENDINGDAY1, new Day1EndingScene() });	// REVISADA 2
	//allScenes.insert({ _ecs::sc_ENDINGDAY2NOKILL, new Day2EndingNoKillScene() });	// REVISADA 2
	//allScenes.insert({ _ecs::sc_ENDINGDAY2KILL, new Day2EndingKillScene() });	// REVISADA 2
	//allScenes.insert({ _ecs::sc_FIRSTDAYAFTERKILL, new FirstDayAfterKillScene() });	// REVISADA 2
	//allScenes.insert({ _ecs::sc_SECONDDAYAFTERKILL, new SecondDayAfterKillScene() });	// REVISADA 2
	//allScenes.insert({ _ecs::sc_NORMALENDING, new NormalEndingScene() });	// REVISADA 2
	//allScenes.insert({ _ecs::sc_BADENDING1, new BadEnding1Scene() });	// REVISADA 2
	//allScenes.insert({ _ecs::sc_BADENDING2, new BadEnding2Scene() });	// REVISADA
	//allScenes.insert({ _ecs::sc_BADENDING3, new BadEnding3Scene() });
	//allScenes.insert({ _ecs::sc_BADENDING4, new BadEnding4Scene() });	// REVISADA 2
	//allScenes.insert({ _ecs::sc_HAPPYENDING, new HappyEndingScene() });	// REVISADA 2

	dailyMenu->buttonPress(0);
	changeScene(allScenes.at(_ecs::sc_SUPERMARKET));
	supermarket->toggleDailyMenu();
}

GameManager::~GameManager() {
	for (auto& sc : allScenes) {
		delete sc.second;
		sc.second = nullptr;
	}

	delete days;
	delete money;
	delete reputation;

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

	if (deleteTransition && deleteScene != nullptr) {
		deleteTransition = false;
		delete deleteScene;
		deleteScene = nullptr;
	}
}
void GameManager::receive(const Message& message) {
	if (!scenes.empty())
		scenes.top()->receive(message);
}


void GameManager::changeScene(Scene* scene, bool longerTransition, bool fadeOut) {
	if (!scenes.empty())
		if (scenes.top() != scene) popScene();

	pushScene(scene);
	if (!longerTransition) {
		deleteScene = new TransitionScene(scene, TRANSITION_TIME, fadeOut);
		scenes.push(deleteScene);
	}
}
void GameManager::popScene(Scene* transitionScene, Scene* scene) {
	if (!scenes.empty()) {
		if (transitionScene != nullptr) {
			deleteTransition = true;
			deleteScene = transitionScene;
		}
		if (scene != nullptr) scene->transitionEnded();

		scenes.pop();
		if (!scenes.empty()) sdlutils().setResizeFactor(scenes.top()->getResizeFactor());
	}
}
void GameManager::pushScene(Scene* scene, bool isTransition) {
	sdlutils().setResizeFactor(scene->getResizeFactor());
	scenes.push(scene);

	if (isTransition)
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


Scene* GameManager::getCurrentScene() { return scenes.top(); }
Scene* GameManager::getScene(_ecs::_scene_id id) { return allScenes.at(id); }

Restaurant* GameManager::getRestaurant() { return restaurant; }
Pantry* GameManager::getPantry() { return pantry; }
SuperMarket* GameManager::getSupermarket() { return supermarket; }
DailyMenuScene* GameManager::getDailyMenu() { return dailyMenu; }
BeforeDayStartScene* GameManager::getBeforeDayStartScene() { return beforeDayStartScene; }


Reputation* GameManager::getReputation() { return reputation; }
Money* GameManager::getMoney() { return money; }
DayManager* GameManager::getDayManager() { return days; }


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


pair<bool, int> GameManager::getHasEverKilled() { return hasEverKilled; }

bool GameManager::getHasKill() { return hasKilled; }
void GameManager::killed() { ++killedNum; }
void GameManager::setHasKill(bool hKill) { hasKilled = hKill; if (!hasEverKilled.first) hasEverKilled = { true,days->getDay() }; }


void GameManager::setGameOver(bool gO) { gameOver = gO; }
bool GameManager::getGameOver() { return gameOver; }

void GameManager::resetScenes() {
	for (auto& sc : allScenes) {
		sc.second->reset();
		sc.second->nextDay();
	}
}



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
	days->setDay(aux, true);

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
	return aux && d != 1;
}

void GameManager::newGame() {
	days->setDay(1, true);
	hasKilled = false;
	hasEverKilled.first = false;
	hasEverKilled.second = 0;
	killedNum = 0;
	gameOver = false;
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
					dialogueInfo dInfo(chr, text, &sdlutils().images().at(prt));

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


void GameManager::initCoopMode(bool server) {
	twoPlayers = true;
	for (auto s : allScenes) {
		s.second->initCoopMode(server);
	}
}
void GameManager::quitCoopMode() {
	twoPlayers = true;
	for (auto s : allScenes) {
		s.second->quitCoopMode();
	}
}

int GameManager::getMasterVolume() {
	return MASTER_VOLUME;
}

void GameManager::setMasterVolume(int nVolume) {
	MASTER_VOLUME = nVolume;
}

int GameManager::getSoundEffectsVolume() {
	return SOUND_EFFECTS;
}

void GameManager::setSoundEffectsVolume(int nVolume) {
	SOUND_EFFECTS = nVolume;
}

std::string GameManager::getCurrentTimeAsString() {
	// Obtener el tiempo actual
	auto now = std::chrono::system_clock::now();

	// Convertir a tiempo de sistema
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

	// Convertir a formato legible
	std::tm localTime;
	localtime_s(&localTime, &currentTime);

	// Crear un buffer para almacenar la fecha y hora formateadas
	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", &localTime);
	return std::string(buffer);
}

void GameManager::saveTestFile(const std::string& name, const std::vector<std::pair<_ecs::_ingredients_id, int>>& ingredients)
{

	std::stringstream file;
	file << "assets/" <<name << getCurrentTimeAsString()<< ".txt";
	std::ofstream write(file.str(), std::ofstream::out);
	if (write.is_open()) {
		for (const auto& ingredient : ingredients) {
			write << ingredientsIdToString(ingredient.first) << ": " << ingredient.second << std::endl;
		}
		write.close();
		std::cout << "Datos guardados en " << file.str() << std::endl;
	}
	else {
		std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
	}
}
