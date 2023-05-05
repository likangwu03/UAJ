#pragma once

#include "../Utilities/Singleton.h"
#include "../Definitions/Food_def.h"
#include "../Definitions/Message_def.h"
#include "../Definitions/Structure_def.h"
#include <string>
#include <deque>
#include <stack>
#include <unordered_map>


class Scene;

class Restaurant;
class Pantry;
class SuperMarket;
class DailyMenuScene;
class BeforeDayStartScene;

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
	dialogueInfo(std::string c, deque<std::string> t, Texture* p) : character(c), text(t), portrait(p) {};
};
class GameManager : public Singleton<GameManager> {
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
	
	std::unordered_map<_ecs::_scene_id, Scene*> allScenes;


	// Escenas de las que se necesita el puntero
	Restaurant* restaurant;
	Pantry* pantry;
	SuperMarket* supermarket;
	DailyMenuScene* dailyMenu;
	BeforeDayStartScene* beforeDayStartScene;

	Reputation* reputation;
	Money* money;
	DayManager* days;

	vector<_ecs::DishInfo>* menu;
	KitchenIslandComp* kitchenIsland;

	bool hasKilled;
	pair<bool,int> hasEverKilled; //si ha matado alguna vez el primer día que mató a un ladrón
	bool mapsCreated;
	bool twoPlayers;
	int killedNum; //número de ladrones matados en el día anterior

	int MASTER_VOLUME = 50; // sonido maestro;
	int SOUND_EFFECTS = 50; // efectos de sonido

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
	void pushScene(Scene* scene, bool isTransition = false);
	void skipfromTransition();
	bool canChangeScene();


	Scene* getCurrentScene();
	Scene* getScene(_ecs::_scene_id id);

	Restaurant* getRestaurant();
	Pantry* getPantry();
	SuperMarket* getSupermarket();
	DailyMenuScene* getDailyMenu();
	BeforeDayStartScene* getBeforeDayStartScene();

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

	vector<dialogueInfo> getDialogueInfo(string d);

	virtual void initCoopMode(bool server);
	virtual void quitCoopMode();

	int getMasterVolume();
	void setMasterVolume(int nVolume);
	int getSoundEffectsVolume();
	void setSoundEffectsVolume(int nVolume);
};