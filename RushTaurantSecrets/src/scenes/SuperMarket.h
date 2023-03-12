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
	Player* player;
	void CreateMap();
public:
	SuperMarket(UIMarket* marketUI = nullptr) : uiMarket(new UIMarket(this) ){ init(); }
	~SuperMarket();
	virtual void initComponent();
	void render();
	void update();
	void handleEvents();
	void init();
	virtual Scene* getConnectedScene() { return uiMarket; }
	CartelManager* getCartelManager() { return cartelM; }
};