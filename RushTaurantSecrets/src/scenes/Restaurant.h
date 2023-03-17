#pragma once
#include "../structure/Scene.h"
#include "../scenes/UIRestaurant.h"
#include "Pantry.h"

class DishCombinator;
class CollisionsManager;
class TextBox;

class Restaurant : public Scene {
private:
	const float RESIZEFACTOR = 0.6666666667;
	Pantry* pantry;
	DishCombinator* dc;
	UIRestaurant* ui;
	CollisionsManager* cm;
	
	GameObject* player;

	vector<_ecs::_dish_id> menu() const;
	void CreateMap();
	vector<_ecs::_dish_id> dailyMenu;

public:
	Restaurant();
	~Restaurant();

	void reset();

	void callAfterCreating();

	UIRestaurant* getUI() { return ui; }
	Pantry* getPantry() { return pantry; }
	void linkPantry(Pantry* pantry);
	void render();
	void update();
	void handleEvents();
	virtual void initComponent();
	// sirve para crear los objetos necesarios
	void init();

	float getResizeFactor() { return RESIZEFACTOR; }
};