#pragma once

#include "../Utilities/Singleton.h"
#include "../Definitions/Food_def.h"
#include <string>

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
class PantryUI;
class IntroScene;
class Texture;
class KitchenIslandComp;

struct dialogueInfo {
	std::string character;
	std::string text;
	Texture* portrait;
public:
	dialogueInfo(std::string c, std::string t, Texture* p) : character(c), text(t), portrait(p) {};
};

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
	PantryUI* pantryUI;
	IntroScene* introScene;

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
	int killedNum; //n��mero de ladrones matados en el d��a anterior
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
	void deleteCurrentScene();
	void skipfromTransition();
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
	ContinueMenu* getContinueMenu();
	EndOfDayScene* getEndOfDay();
	IntroScene* getIntroScene();


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

	vector<dialogueInfo> getDialogueInfo(std::string d);
};