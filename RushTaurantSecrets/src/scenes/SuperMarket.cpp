#include "SuperMarket.h"
#include "../structure/SceneManager.h"

void SuperMarket::render() {
	Scene::render();
}
void SuperMarket::update() {
	Scene::update();
	cm->update();
}
void SuperMarket::handleEvents() {
	Scene::handleEvents();
}
void SuperMarket::init() {
	cm = new CollisionsManager(this);
	new Player(this);
	map = new GameObject(this);
	new MapCreator(map, "./assets/tilemaps/supermarket.tmx", sdlutils().renderer());
}

