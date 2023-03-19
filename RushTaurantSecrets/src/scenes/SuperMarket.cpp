#include "SuperMarket.h"
#include "../structure/GameManager.h"

#include "../utils/checkML.h"

 void SuperMarket::initComponent() {
	 Scene::initComponent();
	 uiMarket->initComponent();
}
void SuperMarket::render() {
	Scene::renderLayer();
	if (uiMarket != nullptr)
		uiMarket->render();
}
void SuperMarket::update() {
	Scene::update();
	cm->update();
	uiMarket->update();
}
void SuperMarket::handleEvents() {
	if (ih->isKeyDown(SDLK_1)) {
		GameManager::get()->changeScene((Scene*)GameManager::get()->getRestaurant());
	}
	else {
		Scene::handleEvents();
		uiMarket->handleEvents();
	}
}

void SuperMarket::init() {
	cm = new CollisionsManager(this);
	player = new Player(this, 0);

}

void SuperMarket::callAfterCreating() {
	cartelM = new CartelManager(this);

	initRender();
	initComponent();
}

void SuperMarket::createMap() {
	Scene::createMap("assets/tilemaps/supermarket.tmx", Down, Vector());
	Scene::createMap("assets/tilemaps/supermarket_top_walls.tmx", Top, Vector());
	Scene::createMap("assets/tilemaps/supermarket_top_bottom.tmx", Middle, Vector(0, 23*48 * RESIZEFACTOR));
	Scene::createMap("assets/tilemaps/supermarket_top_middle.tmx", Middle, Vector(0, 11*48 * RESIZEFACTOR));
}
SuperMarket::~SuperMarket() {
	delete uiMarket;
	delete cm;
	delete cartelM;
}


