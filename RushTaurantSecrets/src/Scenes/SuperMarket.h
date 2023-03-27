#pragma once
#include "../GameObjects/Player.h"
#include "../Managers/CollisionsManager.h"
#include "../Structure/Scene.h"
#include "../Managers/CartelManager.h"
#include "../Components/MapCreator.h"
#include "../Scenes/UIMarket.h"

class SuperMarket: public Scene {
private:
	const float RESIZEFACTOR = 0.6666666667;
	const Vector INITIAL_POS = { 1136, 165 };

	CollisionsManager* cm;
	GameObject* map;
	GameObject* mapTop;
	UIMarket* uiMarket;
	CartelManager* cartelM;
	Player* player;
	
public:
	SuperMarket(UIMarket* marketUI = nullptr) : uiMarket(marketUI == nullptr ? new UIMarket(this) : marketUI),
		cm(nullptr), map(nullptr), mapTop(nullptr), cartelM(nullptr), player(nullptr) { init(); }
	~SuperMarket();
	void reset();
	
	void callAfterCreating();

	virtual void initComponent();
	void render();
	void update();
	void handleEvents();
	void init();
	UIMarket* getUI() { return uiMarket; }
	CartelManager* getCartelManager() { return cartelM; }

	float getResizeFactor() { return RESIZEFACTOR; }
	void createMap();

};