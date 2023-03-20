#include "Restaurant.h"
#include "../structure/GameManager.h"
#include "../objects/DishCombinator.h"
#include "../structure/CollisionsManager.h"
#include "../components/MapCreator.h" 
#include "../gameObjects/Player.h"
#include "../structure/Paths_def.h"
#include "../objects/ClientsManager.h"
#include "../components/FinishDay.h"
#include "../utils/checkML.h"
#include <set>

Restaurant::Restaurant(): dc(DishCombinator::init()), pantry(nullptr) { 
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
	ClientsManager::init(managerContainer, menu(), 6 * 1000, 2, 2);
	new FinishDay(managerContainer);

	createMap();

	initRender();
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

void Restaurant::createMap() {
	Scene::createMap("assets/tilemaps/restaurant.tmx", Down, Vector());
	Scene::createMap("assets/tilemaps/restaurant_top_walls.tmx", Top, Vector());
	Scene::createMap("assets/tilemaps/restaurant_top_kitchenIsland.tmx", Middle, Vector(0, 336 * RESIZEFACTOR));
	Scene::createMap("assets/tilemaps/restaurant_top_table.tmx", Middle, Vector(0, 800 * RESIZEFACTOR));
	Scene::createMap("assets/tilemaps/restaurant_top_counter.tmx", Middle, Vector(0, 507.015 * RESIZEFACTOR));
}


void Restaurant::linkPantry(Pantry* pantry) {
	if(this!=nullptr)this->pantry = pantry;
}

void Restaurant::render() {
	renderLayer();
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
		GameManager::get()->changeScene((Scene*)GameManager::get()->getPantry());
	}
	else if (ih->isKeyDown(SDLK_p)) {
		GameManager::get()->changeScene((Scene*)GameManager::get()->getPauseMenu());
	}
	else if (ih->isKeyDown(SDLK_f)) {
		vector<pair<_ecs::_ingredients_id, int>> _ing;
		_ing.push_back({ POLLO, 3 });
		_ing.push_back({ HUEVO,8 });
		_ing.push_back({ HARINA,11 });
		//_ing.push_back({ AJO,32 });
		//_ing.push_back({ CARNE,4 });
		//_ing.push_back({ FRESA,4 });
		//_ing.push_back({ MANZANA,7 });
		//_ing.push_back({ SALMON,1 });
		//_ing.push_back({ GAMBAS,99 });

		GameManager::get()->setIngredients(_ing);
	}
	else if (ih->isKeyDown(SDLK_g)) {
		vector<pair<_ecs::_ingredients_id, int>> _ing;
		_ing.push_back({ MAIZ, 3 });
		_ing.push_back({ HARINA,8 });
		_ing.push_back({ MOSTAZA,11 });
		_ing.push_back({ PATATA,32 });
		_ing.push_back({ CURRY,4 });
		_ing.push_back({ ARROZ,4 });
		_ing.push_back({ AJO,7 });
		_ing.push_back({ SALCHICHA,1 });
		_ing.push_back({ QUESO,99 });
		_ing.push_back({ HUEVO,19 });

		GameManager::get()->setIngredients(_ing);
	}
	else {
		Scene::handleEvents();
		ui->handleEvents();
	}
}

void Restaurant::refresh() {
	Scene::refresh();
	ui->refresh();
}