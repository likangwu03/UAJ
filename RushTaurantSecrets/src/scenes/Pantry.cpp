#include "Pantry.h"
#include "Restaurant.h"
#include "../structure/SceneManager.h"

#include "../components/MapCreator.h" 
#include "../gameObjects/Player.h"

#include "../utils/checkML.h"
Pantry::Pantry() :rest(nullptr) { init(); }
Pantry::~Pantry() {
	rest->linkPantry(nullptr);
	delete rest;
	delete collisionsManager; // cleon: súper nombre. "con Murcia"? "coge maletas?" "carmen miente"? -> Arreglado
}
void Pantry::init() {
	collisionsManager = new CollisionsManager(this);
	new Player(this);
	GameObject* map = new GameObject(this);
	new MapCreator(map, "assets/tilemaps/pantry.tmx"); // cleon: "./" nunca se necesita -> Arreglado
}

void Pantry::linkRestaurant(Restaurant* rest) {
	if(this!=nullptr)this->rest = rest;
	//ui = rest->getUI();
}

void Pantry::render() {
	Scene::render();
	//ui->render();
}

void Pantry::update() {
	Scene::update();
	//rest->Scene::update();
	collisionsManager->update();
}

void Pantry::handleEvents() {
	if (ih->isKeyDown(SDLK_1)) {
		SceneManager::instance()->ChangeScene(SceneManager::RESTAURANT);
	}
	else if (ih->isKeyDown(SDLK_2)) {
		SceneManager::instance()->ChangeScene(SceneManager::MAINMENU);
	}
	else {
		Scene::handleEvents();
		//ui->handleEvents();
	}
}