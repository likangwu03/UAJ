#pragma once
#include "../Structure/Scene.h"
#include "../Managers/CollisionsManager.h"
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
	void render();
	void update();
	void _update();
	void handleEvents();
	Restaurant* getRestaurant() { return rest; }
	void init();

	float getResizeFactor() { return RESIZEFACTOR; }
	void createMap();

	void callAfterCreating();

};