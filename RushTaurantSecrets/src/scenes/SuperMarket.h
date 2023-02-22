#pragma once
#include "../gameObjects/Player.h"
#include "../structure/CollisionsManager.h"
#include "../structure/Scene.h"
#include "../components/MapCreator.h"
#include "../scenes/UIMarket.h"

class SuperMarket: public Scene {
private:
	CollisionsManager* cm;
	GameObject* map;
	UIMarket* uiMarket;
	//GameObject* mapTop;
public:
	SuperMarket(UIMarket* marketUI = nullptr) : uiMarket(marketUI) { init(); }
	void render();
	void update();
	void handleEvents();
	void init();
};