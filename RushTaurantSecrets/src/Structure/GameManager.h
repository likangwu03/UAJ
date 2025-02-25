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

	bool gameOver;

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

	void setGameOver(bool gO);
	bool getGameOver();

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

	std::string getCurrentTimeAsString();


	// Función para convertir _ingredients_id a string
	std::string ingredientsIdToString(_ecs::_ingredients_id ingredient) {
		static const std::unordered_map<_ecs::_ingredients_id, std::string> ingredientNames = {
			{_ecs::FLOUR, "FLOUR"},
			{_ecs::EGG, "EGG"},
			{_ecs::POTATO, "POTATO"},
			{_ecs::CHOCOLATE, "CHOCOLATE"},
			{_ecs::LETTUCE, "LETTUCE"},
			{_ecs::CORN, "CORN"},
			{_ecs::STRAWBERRY, "STRAWBERRY"},
			{_ecs::CARROT, "CARROT"},
			{_ecs::GARLIC, "GARLIC"},
			{_ecs::MILK, "MILK"},
			{_ecs::RICE, "RICE"},
			{_ecs::TOMATO, "TOMATO"},
			{_ecs::APPLE, "APPLE"},
			{_ecs::BUTTER, "BUTTER"},
			{_ecs::RASPBERRY, "RASPBERRY"},
			{_ecs::MUSTARD, "MUSTARD"},
			{_ecs::NOODLES, "NOODLES"},
			{_ecs::CURRY, "CURRY"},
			{_ecs::CHEESE, "CHEESE"},
			{_ecs::SAUSAGE, "SAUSAGE"},
			{_ecs::CHICKEN, "CHICKEN"},
			{_ecs::PRAWN, "PRAWN"},
			{_ecs::SALMON, "SALMON"},
			{_ecs::MEAT, "MEAT"},
			{_ecs::NONE_ING, "NONE_ING"}
		};	
		//std::cout << ingredientNames.at(ingredient) << "\n";

		return ingredientNames.at(ingredient);
	}


	void saveTestFile(const std::string& name, const std::vector<std::pair<_ecs::_ingredients_id, int>>& ingredients);
};