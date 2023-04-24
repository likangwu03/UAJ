#pragma once

#include "../Utilities/Singleton.h"
#include "../Definitions/Food_def.h"
#include <string>
#include <deque>
#include <stack>
#include"../Definitions/Message_def.h"

class Scene;

class MainMenu;
class BeforeDayStartScene;
class Restaurant;
class UIRestaurant;
class Pantry;
class PantryUI;
class DailyMenuScene;
class SuperMarket;
class EndOfDayScene;
class GameOverScene;

class PauseMenu;
class CoopMenu;
class ContinueMenu;
class OptionsMenu;

class IntroScene;
class FirstDayAfterKillScene;
class SecondDayAfterKillScene;
class BadEnding1Scene;
class EndingDay2NoKill;

class Reputation;
class Money;
class DayManager;
class Texture;
class KitchenIslandComp;
class CinematicBaseScene;


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
	const float TRANSITION_TIME = 0.1;

	stack<Scene*> scenes;
	Scene* deleteScene;
	bool deleteTransition;
	

	//escenas de juego
	Restaurant* restaurant;
	Pantry* pantry;
	SuperMarket* supermarket;
	EndOfDayScene* endScene;
	BeforeDayStartScene* beforeDayStartScene;
	GameOverScene* gameOverScene;

	//ui
	DailyMenuScene* dailyMenu;
	PantryUI* pantryUI;

	//menu
	MainMenu* mainMenu;
	OptionsMenu* optionsMenu;
	PauseMenu* pauseMenu;
	ContinueMenu* continueMenu;
	CoopMenu* coopMenu;


	Reputation* reputation;
	Money* money;
	DayManager* days;

	vector<_ecs::DishInfo>* menu;
	KitchenIslandComp* kitchenIsland;

	bool hasKilled;
	pair<bool,int> hasEverKilled; //si ha matado alguna vex/ el primer d¨ªa que mat¨® a un ladr¨®n
	bool mapsCreated;
	bool twoPlayers;
	int killedNum; //n¨²mero de ladrones matados en el d¨ªa anterior


	//escenas cinem¨¢ticas
	IntroScene* introScene;
	FirstDayAfterKillScene* firstDayAfterKillScene;
	SecondDayAfterKillScene* secondDayAfterKillScene;
	BadEnding1Scene* badEnding1Scene;
	EndingDay2NoKill* endingDay2NoKill;

	GameManager();

public:
	void initialize();
	~GameManager();

	void update();
	void handleEvents();
	void render();
	void refresh();
	void receive(const Message& message);

	void changeScene(Scene* scene, bool longerTransition = false, bool fadeOut = false);
	void popScene(Scene* transitionScene = nullptr, Scene* cinematic = nullptr);
	void pushScene(Scene* scene, bool longerTransition = false);
	void skipfromTransition();
	bool canChangeScene();

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
	CoopMenu* getCoopMenu();
	EndOfDayScene* getEndOfDay();
	IntroScene* getIntroScene();
	FirstDayAfterKillScene* getFirstDayAfterKillScene();
	SecondDayAfterKillScene * getSecondDayAfterKillScene();
	BadEnding1Scene* getBadEnding1Scene();
	EndingDay2NoKill* getEndingDay2NoKillScene();

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

	void resetScenes();
	void save();
	void load();
	bool checkload();
	void newGame();

	vector<dialogueInfo> getDialogueInfo(std::string d);
};