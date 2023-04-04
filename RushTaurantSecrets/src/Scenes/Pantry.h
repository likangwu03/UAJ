#pragma once
#include "../Structure/Scene.h"
#include "../Managers/CollisionsManager.h"
#include "../GameObjects/Clock.h"
#include "../Scenes/PantryUI.h"

class Restaurant;

class Pantry : public Scene {
private:
	const float RESIZEFACTOR = 0.8333333333;
	GameObject* player;
	CollisionsManager* collisionsManager;
	Restaurant* rest;
	PantryUI* pantryUI;

public:
	Pantry(PantryUI* pUI);
	~Pantry();
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