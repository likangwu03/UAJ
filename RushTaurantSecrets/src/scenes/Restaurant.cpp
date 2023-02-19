#include "Restaurant.h"
#include "Pantry.h"
#include "../structure/SceneManager.h"
#include "../components/CookingMachineComp.h"
#include "../gameObjects/Client.h"
#include "../structure/Paths_def.h"
#include "../objects/ClientsManager.h"

void Restaurant::linkPantry(Pantry* pantry) {
	this->pantry = pantry;
}

void Restaurant::render() {
	Scene::render();
	if (ui != nullptr)
	ui->render();
}

void Restaurant::update() {
	Scene::update();
	if(pantry!=nullptr)
	pantry->Scene::update();
	ui->update();
	cm->update();
}

void Restaurant::handleEvents() {
	if (ih->isKeyDown(SDLK_1)) {
		SceneManager::instance()->ChangeScene(SceneManager::PANTRY);
	}
	else if (ih->isKeyDown(SDLK_2)) {
		SceneManager::instance()->ChangeScene(SceneManager::MAINMENU);
	}
	else {
		Scene::handleEvents();
		//ui->handleEvents();
	}

}
void Restaurant::init() {
	
	cm = new CollisionsManager(this);
	ui = new UIRestaurant();
	new Player(this);
	
	// Tilemap de prueba
	map = new GameObject(this);
	new MapCreator(map, "./assets/tilemaps/restaurant.tmx", sdlutils().renderer());

	// menu
	vector<_ecs::_dish_id> menu;
	menu.push_back(_ecs::HUEVO_FRITO);
	menu.push_back(_ecs::PANCAKE);
	GameObject* managerContainer = new GameObject(this);
	ClientsManager::init(managerContainer, menu, 5 * 1000);
	/*
	// Tilemap de prueba
	mapTop = new GameObject(this, _ecs::grp_RENDERTOP);
	new MapCreator(mapTop, "./assets/tilemaps/restaurant_top.tmx", sdlutils().renderer());
	*/
	
	// objetos interactuables
	//new Bin(this, Vector(1100, 70));
}