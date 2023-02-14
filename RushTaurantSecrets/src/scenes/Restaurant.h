#pragma once
#include "../structure/Scene.h"
#include "../scenes/UIRestaurant.h"

class Pantry;

class Restaurant : public Scene {
private:
	Pantry* pantry;
	UIRestaurant* ui;
public:
	Restaurant(UIRestaurant* restUI=nullptr) : pantry(nullptr), ui(restUI) { }
	UIRestaurant* getUI() { return ui; }
	Pantry* getPantry() { return pantry; }
	void linkPantry(Pantry* pantry);
	void render();
	void update();
	void handleEvents();
};