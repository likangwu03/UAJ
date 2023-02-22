#pragma once
#include "../gameObjects/Player.h"
#include "../structure/CollisionsManager.h"
#include "../structure/Scene.h"
#include "../components/MapCreator.h"

class SuperMarket: public Scene {
private:
	CollisionsManager* cm;
	GameObject* map;
	//GameObject* mapTop;
public:
	SuperMarket(){ init(); }
	void render();
	void update();
	void handleEvents();
	void init();
};