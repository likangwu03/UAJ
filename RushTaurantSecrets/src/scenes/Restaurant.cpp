#include "Restaurant.h"
#include "Pantry.h"
#include "../structure/SceneManager.h"
#include "../components/CookingMachineComp.h"
#include "../gameObjects/Client.h"
#include "../structure/Paths_def.h"
#include "../objects/ClientsManager.h"

#include "../components/MapCreator.h"

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

	// menu
	vector<_ecs::_dish_id> menu;
	menu.push_back(_ecs::TARTA_QUESO);
	menu.push_back(_ecs::PANCAKE);
	// manager de clientes
	GameObject* managerContainer = new GameObject(this);
	ClientsManager::init(managerContainer, menu, 6 * 1000, 2, 10);
	
	cm = new CollisionsManager(this);
	ui = new UIRestaurant();
	new Player(this);
	
	// Tilemap de prueba
	map = new GameObject(this);
	new MapCreator(map, "./assets/tilemaps/restaurant.tmx", sdlutils().renderer());

	/*
	// Tilemap de prueba
	mapTop = new GameObject(this, _ecs::grp_RENDERTOP);
	new MapCreator(mapTop, "./assets/tilemaps/restaurant_top.tmx", sdlutils().renderer());
	*/
	
	// objetos interactuables
	//new Bin(this, Vector(1100, 70));


	// Men?del día aleatorio (genera un número de platos aleatorio entre 1-5 platos, lo
		// rellena con platos diferentes entre s? y los pasa a un vector para poder acceder a ellos)
		// Menú del día aleatorio (genera un número de platos aleatorio entre 1-5 platos, lo
		// rellena con platos diferentes entre sí, y los pasa a un vector para poder acceder a ellos)
		/*set<int> aux;
		int auxSize = rand() % 5 + 1;
		for (int i = 0; i < auxSize; i++) {
			if (!aux.insert(rand() % _ecs::NONE_DISH).second)
				i--;
		}*/
		/*vector<int> menu;
		for (auto i = aux.begin(); i != aux.end(); ++i) menu.push_back(*i);

		new ClientState(client, menu);

		SDLUtils* sdl = SDLUtils::instance();
		*/

}