#include "Restaurant.h"
#include "Pantry.h"
#include "../structure/SceneManager.h"
#include "../components/CookingMachineComp.h"

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

	
	// objetos interactuables
	//new Bin(this, Vector(1100, 70));
}