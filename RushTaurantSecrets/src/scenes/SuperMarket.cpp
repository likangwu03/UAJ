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
	if (ih->isKeyDown(SDLK_1)) {
		SceneManager::instance()->changeScene(new Restaurant(), 1);
	}
	else {
		Scene::handleEvents();
		uiMarket->handleEvents();
	}
}

void SuperMarket::init() {
	cm = new CollisionsManager(this);
	player = new Player(this);
	//cartelM = new CartelManager();
	cartelM = CartelManager::instance();
	map = new GameObject(this);
	new MapCreator(map, "assets/tilemaps/supermarket.tmx");
	mapTop = new GameObject(this, _ecs::grp_RENDERTOP);
	new MapCreator(mapTop, "assets/tilemaps/supermarket_top.tmx");
}

SuperMarket::~SuperMarket() {
	delete uiMarket;
	delete cm;
}


