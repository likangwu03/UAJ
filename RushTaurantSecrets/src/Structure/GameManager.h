#pragma once

#include "../Utilities/Singleton.h"
#include "../Definitions/Food_def.h"
#include <string>
#include <deque>

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
class Texture;
class KitchenIslandComp;
class IntroScene;
class FirstDayAfterKillScene;
class SecondDayAfterKillScene;

struct dialogueInfo {
	std::string character;
	deque<std::string> text;
	Texture* portrait;
public:
	dialogueInfo(std::string c, deque<std::string> t, Texture* p) : character(c), text(t), portrait(p) {};
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
	
	//escenas de juego
	Restaurant* restaurant;
	Pantry* pantry;
	SuperMarket* supermarket;

	//ui
	DailyMenuScene* dailyMenu;
	UIRestaurant* uiRestaurant;
	PantryUI* pantryUI;

	//menu
	MainMenu* mainMenu;
	OptionsMenu* optionsMenu;
	PauseMenu* pauseMenu;
	ContinueMenu* continueMenu;
	EndOfDayScene* endScene;
	BeforeDayStartScene* beforeDayStartScene;
	GameOverScene* gameOverScene;
	
	//escenas cinem¨¢ticas
	IntroScene* introScene;
	FirstDayAfterKillScene* firstDayAfterKillScene;
	SecondDayAfterKillScene* secondDayAfterKillScene;

	Reputation* reputation;
	Money* money;
	DayManager* days;

	vector<_ecs::DishInfo>* menu;
	KitchenIslandComp* kitchenIsland;

	float dayTime;
	//bool multiplayer;
	bool hasKilled;
	pair<bool,int> hasEverKilled; //si ha matado alguna vex/ el primer d¨ªa que mat¨® a un ladr¨®n
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
	FirstDayAfterKillScene* getFirstDayAfterKillScene();
	SecondDayAfterKillScene * getSecondDayAfterKillScene();


	Reputation* getReputation();
	Money* getMoney();
	DayManager* getDayManager();

	vector<_ecs::DishInfo>* getTodaysMenu();
	void setTodaysMenu(vector<_ecs::DishInfo>* tmenu);

	void setKichenIsland(KitchenIslandComp* KIComp);
	void setIngredients(vector<pair<_ecs::_ingredients_id, int>> ing);
	
	pair<bool, int> getHasEverKilled();
	bool getHasKill();
	void setHasKill(bool hKill);
	void killed();

	void save();
	void load();
	bool checkload();
	void newGame();

	vector<dialogueInfo> getDialogueInfo(std::string d);
};