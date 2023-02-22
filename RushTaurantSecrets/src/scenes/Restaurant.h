#pragma once
#include "../structure/Scene.h"
#include "../scenes/UIRestaurant.h"
#include "../gameObjects/Player.h"
#include "../objects/DishCombinator.h"
#include "../gameObjects/CookingMachine.h"
#include "../gameObjects/Bin.h"
#include "../structure/CollisionsManager.h"
//#include "../gameObjects/Inventory.h" //de momento est¨¢ aqu¨ª, no s¨¦ si moverlo a UI

class Pantry;
class Restaurant : public Scene {
private:
	Pantry* pantry;
	DishCombinator* dc;
	UIRestaurant* ui;
	CollisionsManager* cm;
	GameObject* map;
	GameObject* mapTop;

public:
	Restaurant(UIRestaurant* restUI = nullptr) : pantry(nullptr), ui(restUI),dc(DishCombinator::init()) { init(); }
	UIRestaurant* getUI() { return ui; }
	Pantry* getPantry() { return pantry; }
	void linkPantry(Pantry* pantry);
	void render();
	void update();
	void handleEvents();
	// sirve para crear los objetos necesarios
	void init();
};