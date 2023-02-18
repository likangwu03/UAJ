#pragma once
#include "../structure/Scene.h"
#include "../scenes/UIRestaurant.h"
#include "../gameObjects/Player.h"
#include "../structure/DishCombinator.h"
#include "../gameObjects/CookingMachine.h"
#include "../gameObjects/Bin.h"
//#include "../gameObjects/Inventory.h" //de momento est¨¢ aqu¨ª, no s¨¦ si moverlo a UI

class Pantry;
class Restaurant : public Scene {
private:
	Pantry* pantry;
	DishCombinator* dc;
	UIRestaurant* ui;
public:
	Restaurant(UIRestaurant* restUI = nullptr) : pantry(nullptr), ui(restUI),dc(DishCombinator::init()) { init(); }
	UIRestaurant* getUI() { return ui; }
	Pantry* getPantry() { return pantry; }
	void linkPantry(Pantry* pantry);
	void render();
	void update();
	void handleEvents();
	void init(); //de momento est¨¢ como un m¨¦todo aparte y no se ha llamado, sirve para crear los objects necesarios
};