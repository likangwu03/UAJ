#pragma once

#include "../utils/Singleton.h"
#include "../structure/Food_def.h"

class Scene;
class MainMenu;
class BeforeDayStartScene;
class Restaurant;
class Pantry;
class DailyMenuScene;
class SuperMarket;
class PauseMenu;
class Reputation;
class Money;

class GameManager :public Singleton<GameManager> {
	friend Singleton<GameManager>;

public:
	GameManager(GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator=(GameManager&) = delete;
	GameManager& operator=(GameManager&&) = delete;

	
private:
	const float RESTSUPERSIZE = 0.6666666667;
	const float PANTRYSIZE = 0.8333333333;

	Scene* currentScene;
	Scene* previousScene;
	MainMenu* mainMenu;
	BeforeDayStartScene* beforeDayStartScene;
	Restaurant* restaurant;
	Pantry* pantry;
	DailyMenuScene* dailyMenu;
	SuperMarket* supermarket;
	PauseMenu* pauseMenu;

	Reputation* reputation;
	Money* money;
	vector<_ecs::DishInfo>* menu;

	float dayTime;
	//bool multiplayer;
	bool hasKilled;
	bool gameOver;

	GameManager();

public:
	void initialize();
	~GameManager();

	void update();
	void handleEvents();
	void render();
	void refresh();

	void changeScene(Scene* scene);
	void popScene();
	Scene* getCurrentScene();
	MainMenu* getMainMenu();
	Restaurant* getRestaurant();
	Pantry* getPantry();
	DailyMenuScene* getDailyMenu();
	SuperMarket* getSupermarket();
	PauseMenu* getPauseMenu();
	BeforeDayStartScene* getBeforeDayStart();

	Reputation* getReputation();
	Money* getMoney();
	vector<_ecs::DishInfo>* getTodaysMenu();
	void setTodaysMenu(vector<_ecs::DishInfo>* tmenu);

	bool getHasKill();
	void setHasKill(bool hKill);

};