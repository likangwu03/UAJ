#pragma once
#include "../structure/Scene.h"

class Restaurant;

class Pantry : public Scene {
private:
	Restaurant* rest;
public:
	Pantry() : rest(nullptr) { }
	~Pantry() { }
	void linkRestaurant(Restaurant* rest);
	void render();
	void update();
	void handleEvents();
	Restaurant* getRestaurant() { return rest; }
};