#include "Pantry.h"
#include "Restaurant.h"
#include "../structure/SceneManager.h"

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
	new Player(this, 0);

	// el update no se ejecuta hasta que se está en la escena
	// por lo que no se crean ni se destruyen ladrones cuandon no se está en la despensa
	GameObject* managerContainer = new GameObject(this);
	ThiefsManager::init(managerContainer, 2, 6, true, 4 * 1000);

	GameObject* map = new GameObject(this);
	new MapCreator(map, "assets/tilemaps/pantry.tmx");
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
		SceneManager::instance()->setResize();
		SceneManager::instance()->changeScene(rest, -1);
	}
	else if (ih->isKeyDown(SDLK_2)) {
		SceneManager::instance()->setResize();
		SceneManager::instance()->changeScene(nullptr,1);
	}
	else {
		Scene::handleEvents();
		//ui->handleEvents();
	}
}