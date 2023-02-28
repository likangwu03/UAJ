#pragma once
#include "../gameObjects/Player.h"
#include "../structure/CollisionsManager.h"
#include "../structure/Scene.h"
#include "../structure/CartelManager.h"
#include "../components/MapCreator.h"
#include "../scenes/UIMarket.h"

class SuperMarket: public Scene {
private:
	CollisionsManager* cm;
	GameObject* map;
	GameObject* mapTop;
	UIMarket* uiMarket;
	CartelManager* cartelM;
	GameObject* player;
	//GameObject* mapTop;
public:
	SuperMarket(UIMarket* marketUI = nullptr) : uiMarket(marketUI) { init(); }
	~SuperMarket();
	void render();
	void update();
	void handleEvents();
	void init();
	CartelManager* getCartelManager() { return cartelM; }
};