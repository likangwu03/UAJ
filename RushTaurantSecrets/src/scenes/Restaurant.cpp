#include "Restaurant.h"

#include "../structure/GameManager.h"

#include "../objects/DishCombinator.h"
#include "../structure/CollisionsManager.h"

#include "../components/MapCreator.h" 
#include "../gameObjects/Player.h"


#include "../structure/Paths_def.h"
#include "../objects/ClientsManager.h"

#include <set>

#include "../utils/checkML.h"


Restaurant::Restaurant(): dc(DishCombinator::init()) { 
	ui = new UIRestaurant();
	cm = new CollisionsManager(this);
	player = new Player(this, 0);
}

Restaurant::~Restaurant() {
	pantry->linkRestaurant(nullptr);
	delete ui;
	delete cm;
}

void Restaurant::reset() {
	player->getComponent<PlayerMovementController>()->initP();
}


void Restaurant::callAfterCreating() {
	// clientsManager
	GameObject* managerContainer = new GameObject(this);
	clientsManager = ClientsManager::init(managerContainer, menu(), 6 * 1000, 2, 2);
	CreateMap();
	initRender();

	// las mesas se inicializan luego de haberse creado
	//clientsManager->initTables();

	initComponent();
}


vector<_ecs::_dish_id> Restaurant::menu() const {
	// Men?del d�a aleatorio (lo rellena con 4 platos diferentes
	// entre s?y los pasa a un vector para poder acceder a ellos)
	set<int> aux;
	for (int i = 0; i < 4; i++) {
		if (!aux.insert(rand() % _ecs::NONE_DISH).second)
			i--;
	}
	vector<_ecs::_dish_id> menu;
	for (auto i = aux.begin(); i != aux.end(); ++i) menu.push_back((_ecs::_dish_id)*i);

	return menu;
}


void Restaurant::CreateMap() {
	Scene::CreateMap("assets/tilemaps/restaurant.tmx", Down, Vector());
	Scene::CreateMap("assets/tilemaps/restaurant_top_walls.tmx", Top, Vector());
	Scene::CreateMap("assets/tilemaps/restaurant_top_kitchenIsland.tmx", Middle, Vector(0, 336 * sdlutils().getResizeFactor()));
	Scene::CreateMap("assets/tilemaps/restaurant_top_table.tmx", Middle, Vector(0, 768 * sdlutils().getResizeFactor()));
	Scene::CreateMap("assets/tilemaps/restaurant_top_counter.tmx", Middle, Vector(0, 507.015 * sdlutils().getResizeFactor()));
}


void Restaurant::linkPantry(Pantry* pantry) {
	if(this!=nullptr)this->pantry = pantry;
}

void Restaurant::render() {
	renderLayer();
	//Scene::render();
	if (ui != nullptr)
	ui->render();
}

void Restaurant::initComponent() {
	Scene::initComponent();
	ui->initComponent();
}
void Restaurant::update() {
	Scene::update();
	pantry->Scene::update();
	ui->update();
	cm->update();
}
void Restaurant::handleEvents() {
	if (ih->isKeyDown(SDLK_1)) {
		GameManager::instance()->changeScene((Scene*)GameManager::instance()->getPantry());
	}
	else if (ih->isKeyDown(SDLK_p)) {
		GameManager::instance()->changeScene((Scene*)GameManager::instance()->getPauseMenu());
	}
	else {
		Scene::handleEvents();
	}
}