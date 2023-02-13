#pragma once
#include "../structure/Scene.h"
#include "../scenes/UI.h"

class Restaurant;

class Pantry : public Scene {
private:
	Restaurant* rest;
	UI* ui;
public:
	Pantry() : rest(nullptr), ui(nullptr) { }
	~Pantry() { }
	void linkRestaurant(Restaurant* rest);
	void render();
	void update();
	void handleEvents();
};