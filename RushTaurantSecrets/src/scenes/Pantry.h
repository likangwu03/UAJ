#pragma once
#include "../structure/Scene.h"
#include "../structure/CollisionsManager.h"
class Restaurant;

class Pantry : public Scene {
private:
	const float RESIZEFACTOR = 0.8333333333;
	GameObject* player;
	CollisionsManager* collisionsManager;
	Restaurant* rest;

public:
	Pantry();
	~Pantry();
	void reset();
	void linkRestaurant(Restaurant* rest);
	void render();
	void update();
	void handleEvents();
	Restaurant* getRestaurant() { return rest; }
	void init();

	float getResizeFactor() { return RESIZEFACTOR; }
	void createMap();

};