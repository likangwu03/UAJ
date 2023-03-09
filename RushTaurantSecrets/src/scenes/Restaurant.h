#pragma once
#include "../structure/Scene.h"

#include "Pantry.h"
class DishCombinator;
#include "../scenes/UIRestaurant.h"
class CollisionsManager;
class ClientsManager;

class Restaurant : public Scene {
private:
	Pantry* pantry;
	DishCombinator* dc;
	UIRestaurant* ui;
	CollisionsManager* cm;
	GameObject* map;
	GameObject* mapTop;
	GameObject* player;
	ClientsManager* clientsManager;

	vector<_ecs::_dish_id> menu() const;

public:
	Restaurant();
	~Restaurant();

	UIRestaurant* getUI() { return ui; }
	Pantry* getPantry() { return pantry; }
	void linkPantry(Pantry* pantry);
	void render();
	void update();
	void handleEvents();
	// sirve para crear los objetos necesarios
	void init();
};