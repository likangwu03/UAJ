#include "SuperMarket.h"
#include "../structure/SceneManager.h"

#include "../utils/checkML.h"

void SuperMarket::render() {
	Scene::render();
	if (uiMarket != nullptr)
		uiMarket->render();
}
void SuperMarket::update() {
	Scene::update();
	cm->update();
	uiMarket->update();
}
void SuperMarket::handleEvents() {
	Scene::handleEvents();
}

void SuperMarket::init() {
	cm = new CollisionsManager(this);
	player = new Player(this);
	cartelM = new CartelManager();
	map = new GameObject(this);
	new MapCreator(map, "./assets/tilemaps/supermarket.tmx", sdlutils().renderer());
}

SuperMarket::~SuperMarket() {
	delete uiMarket;
	delete cm;
	delete cartelM;
}


