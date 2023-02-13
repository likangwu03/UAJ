#pragma once
#include "../structure/Scene.h"
#include "../scenes/UI.h"

class Pantry;

class Restaurant : public Scene {
private:
	Pantry* pantry;
	UI* ui;
public:
	Restaurant(UI* restUI) : pantry(nullptr), ui(restUI) { }
	UI* getUI() { return ui; }
	void linkPantry(Pantry* pantry);
	void render();
	void update();
	void handleEvents();
};