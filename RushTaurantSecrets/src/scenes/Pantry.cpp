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
	new Player(this, 0);

	// el update no se ejecuta hasta que se est?en la escena
	// por lo que no se crean ni se destruyen ladrones cuandon no se est?en la despensa
	GameObject* managerContainer = new GameObject(this);
	ThiefsManager::init(managerContainer, 2, 6, false, 4 * 1000, 2);
	CreateMap();
	initRender();

	Scene::initComponent();
}

void Pantry::CreateMap() {
	Scene::CreateMap("assets/tilemaps/pantry.tmx", Down, Vector());
	Scene::CreateMap("assets/tilemaps/pantry_top_walls.tmx", Top, Vector());
	Scene::CreateMap("assets/tilemaps/pantry_top_bottom.tmx", Middle, Vector(0, 14*48 * sdlutils().getResizeFactor()));
	Scene::CreateMap("assets/tilemaps/pantry_top_middle.tmx", Middle, Vector(0, 11*48 * sdlutils().getResizeFactor()));
	Scene::CreateMap("assets/tilemaps/pantry_top_bottom_2.tmx", Middle, Vector(0, 16*48 * sdlutils().getResizeFactor()));
}

void Pantry::linkRestaurant(Restaurant* rest) {
	if(this!=nullptr)this->rest = rest;
	//ui = rest->getConnectedScene();
}

void Pantry::render() {
	Scene::renderLayer();
	//Scene::render();
	//ui->render();
}

void Pantry::update() {
	Scene::update();
	//rest->Scene::update();
	collisionsManager->update();
}

void Pantry::handleEvents() {
	if (ih->isKeyDown(SDLK_1)) {
		GameManager::instance()->changeScene(GameManager::instance()->getRestaurant());
	}
	else {
		Scene::handleEvents();
		//ui->handleEvents();
	}
}