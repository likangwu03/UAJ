#include "Pantry.h"
#include "Restaurant.h"
#include "../structure/GameManager.h"
#include "../components/MapCreator.h" 
#include "../gameObjects/Player.h"
#include "../objects/ThiefsManager.h"
#include "../utils/checkML.h"

Pantry::Pantry() :rest(nullptr) { init(); }
Pantry::~Pantry() {
	rest->linkPantry(nullptr);
	delete rest;
	delete collisionsManager;
}
void Pantry::init() {
	collisionsManager = new CollisionsManager(this);

	// el update no se ejecuta hasta que se est?en la escena
	// por lo que no se crean ni se destruyen ladrones cuandon no se est?en la despensa
	GameObject* managerContainer = new GameObject(this);
	ThiefsManager::init(managerContainer, 2, 6, GameManager::get()->getHasKill(), 4 * 1000, 2);

	initRender();
	Scene::initComponent();
}

void Pantry::createMap() {
	Scene::createMap("assets/tilemaps/pantry.tmx", Down, Vector());
	Scene::createMap("assets/tilemaps/pantry_top_walls.tmx", Top, Vector());
	Scene::createMap("assets/tilemaps/pantry_top_bottom.tmx", Middle, Vector(0, 14*48 * RESIZEFACTOR));
	Scene::createMap("assets/tilemaps/pantry_top_middle.tmx", Middle, Vector(0, 11*48 * RESIZEFACTOR));
	Scene::createMap("assets/tilemaps/pantry_top_bottom_2.tmx", Middle, Vector(0, 16*48 * RESIZEFACTOR));
}

void Pantry::linkRestaurant(Restaurant* rest) {
	if(this!=nullptr)this->rest = rest;
}

void Pantry::render() {
	Scene::renderLayer();
}

void Pantry::update() {
	Scene::update();
	collisionsManager->update();
}

void Pantry::handleEvents() {
	if (ih->isKeyDown(SDLK_1)) {
		GameManager::get()->changeScene(GameManager::get()->getRestaurant());
	}
	else {
		Scene::handleEvents();
	}
}