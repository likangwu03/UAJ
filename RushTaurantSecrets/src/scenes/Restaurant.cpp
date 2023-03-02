#include "Restaurant.h"

#include "../objects/DishCombinator.h"
#include "../structure/CollisionsManager.h"
#include "../components/MapCreator.h" 
#include "../gameObjects/Player.h"

#include "../structure/Paths_def.h"
#include "../objects/ClientsManager.h"
#include "../objects/ThiefsManager.h"

#include "../structure/SceneManager.h"
#include <set>

#include "../utils/checkML.h"


Restaurant::Restaurant(): dc(DishCombinator::init()) { 
	ui = new UIRestaurant();
	SceneManager::instance()->setResize(false);
	pantry = new Pantry();
	pantry->linkRestaurant(this);
	SceneManager::instance()->setResize();
	init(); 
}

Restaurant::~Restaurant() {
	end();
	pantry->linkRestaurant(nullptr);
	delete pantry;
	delete ui;
	delete cm;
}

void Restaurant::init() {
	// Menú del día aleatorio (lo rellena con 4 platos diferentes
	// entre sí y los pasa a un vector para poder acceder a ellos)
	set<int> aux;
	for (int i = 0; i < 4; i++) {
		if (!aux.insert(rand() % _ecs::NONE_DISH).second)
			i--;
	}
	vector<_ecs::_dish_id> menu;
	for (auto i = aux.begin(); i != aux.end(); ++i) menu.push_back((_ecs::_dish_id)*i);


	// manager de clientes
	GameObject* managerContainer = new GameObject(this);
	ClientsManager::init(managerContainer, menu, 6 * 1000, 2, 2);
	ThiefsManager::init(managerContainer, 2, 6, true, 5 * 1000);
	// me da un error raro
	// ManagerContainer(menu, 6, 2, 10, 2, 6, true, 5);
	
	cm = new CollisionsManager(this);
	player = new Player(this);
	
	// Tilemap
	map = new GameObject(this);
	new MapCreator(map, "assets/tilemaps/restaurant.tmx");
	mapTop = new GameObject(this, _ecs::grp_RENDERTOP);
	new MapCreator(mapTop, "assets/tilemaps/restaurant_top.tmx");

	
	// objetos interactuables
	//new Bin(this, Vector(1100, 70));

}

void Restaurant::linkPantry(Pantry* pantry) {
	if(this!=nullptr)this->pantry = pantry;
}

void Restaurant::render() {
	Scene::render();
	if (ui != nullptr)
	ui->render();
}

void Restaurant::update() {
	Scene::update();
	//if(pantry!=nullptr)
	//pantry->Scene::update();
	ui->update();
	cm->update();
}

void Restaurant::handleEvents() {
	if (ih->isKeyDown(SDLK_1)) {
		SceneManager::instance()->setResize(false);
		SceneManager::instance()->changeScene(pantry,-1);
	}
	else if (ih->isKeyDown(SDLK_2)) {
		SceneManager::instance()->changeScene(nullptr,1);
	}
	else if (ih->isKeyDown(SDL_SCANCODE_P)) {
		SceneManager::instance()->changeScene(new PauseMenu());
	}
	else {
		Scene::handleEvents();
		//ui->handleEvents();
	}
}