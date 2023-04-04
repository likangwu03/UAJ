#pragma once

#include "../Utilities/Singleton.h"
#include "../Definitions/Food_def.h"

class Scene;
class MainMenu;
class BeforeDayStartScene;
class Restaurant;
class UIRestaurant;
class Pantry;
class DailyMenuScene;
class SuperMarket;
class PauseMenu;
class OptionsMenu;
class Reputation;
class Money;
class DayManager;
class EndOfDayScene;
class GameOverScene;
class ContinueMenu;

class KitchenIslandComp;

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
	UIRestaurant* uiRestaurant;
	Pantry* pantry;
	DailyMenuScene* dailyMenu;
	SuperMarket* supermarket;
	PauseMenu* pauseMenu;
	OptionsMenu* optionsMenu;
	EndOfDayScene* endScene;
	GameOverScene* gameOverScene;
	ContinueMenu* continueMenu;


	Reputation* reputation;
	Money* money;
	DayManager* days;

	vector<_ecs::DishInfo>* menu;
	KitchenIslandComp* kitchenIsland;

	float dayTime;
	//bool multiplayer;
	bool hasKilled;
	bool mapsCreated;
	bool twoPlayers;
	int killedNum; //n¨²mero de ladrones matados en el d¨ªa anterior
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
	void setGameOver(int type);
	Scene* getCurrentScene();
	MainMenu* getMainMenu();
	Restaurant* getRestaurant();
	Pantry* getPantry();
	DailyMenuScene* getDailyMenu();
	SuperMarket* getSupermarket();
	PauseMenu* getPauseMenu();
	OptionsMenu* getOptionsMenu();
	BeforeDayStartScene* getBeforeDayStart();
	EndOfDayScene* getEndOfDay();
	ContinueMenu* getContinueMenu();

	Reputation* getReputation();
	Money* getMoney();
	DayManager* getDayManager();

	vector<_ecs::DishInfo>* getTodaysMenu();
	void setTodaysMenu(vector<_ecs::DishInfo>* tmenu);

	void setKichenIsland(KitchenIslandComp* KIComp);
	void setIngredients(vector<pair<_ecs::_ingredients_id, int>> ing);

	bool getHasKill();
	void setHasKill(bool hKill);
	void killed();

	void save();
	void load();
	bool checkload();
	void newGame();
};