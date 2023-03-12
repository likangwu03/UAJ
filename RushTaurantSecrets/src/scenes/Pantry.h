#pragma once
#include "../structure/Scene.h"
#include "../structure/CollisionsManager.h"
class Restaurant;

class Pantry : public Scene {
private:
	CollisionsManager* collisionsManager;
	Restaurant* rest;
	void CreateMap();

public:
	Pantry();
	~Pantry();
	void linkRestaurant(Restaurant* rest);
	void render();
	void update();
	void handleEvents();
	Restaurant* getRestaurant() { return rest; }
	void init();
};