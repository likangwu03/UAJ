#pragma once
#include "../structure/Scene.h"
#include "../scenes/UIRestaurant.h"
#include "Pantry.h"

class DishCombinator;
class CollisionsManager;
class TextBox;

class Restaurant : public Scene {
private:
	Pantry* pantry;
	DishCombinator* dc;
	UIRestaurant* ui;
	CollisionsManager* cm;
	
	GameObject* player;

	vector<_ecs::_dish_id> menu() const;
	void CreateMap();
	

public:
	Restaurant();
	~Restaurant();

	UIRestaurant* getConnectedScene() { return ui; }
	Pantry* getPantry() { return pantry; }
	void linkPantry(Pantry* pantry);
	void render();
	void update();
	void handleEvents();
	virtual void initComponent();
	// sirve para crear los objetos necesarios
	void init();
};