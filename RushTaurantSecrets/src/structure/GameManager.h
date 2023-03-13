#pragma once

#include "../utils/Singleton.h"

class Scene;
class MainMenu;
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
	Scene* currentScene;
	Scene* previousScene;
	MainMenu* mainMenu;
	Restaurant* restaurant;
	Pantry* pantry;
	DailyMenuScene* dailyMenu;
	SuperMarket* supermarket;
	PauseMenu* pauseMenu;

	Reputation* reputation;
	Money* money;

	float dayTime;
	bool multiplayer;
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
	Scene* getMainMenu();
	Scene* getRestaurant();
	Scene* getPantry();
	Scene* getDailyMenu();
	Scene* getSupermarket();
	Scene* getPauseMenu();

	Reputation* getReputation();
	Money* getMoney();

	bool getHasKill();
	void setHasKill(bool hKill);

};