#pragma once
#include "../structure/Scene.h"
#include "../../prueba.h"
#include "../../src/components/MapCreator.h"
#include "../structure/Structure_def.h"
#include "../structure/Food_def.h"
#include "../structure/CollisionsManager.h"

class MainMenu : public Scene {
private:
	CollisionsManager* cManager;
	InputHandler* ih;
	GameObject* map;
	GameObject* test;

public:
	~MainMenu() {
		delete cManager;
	}
	MainMenu() :Scene() {
		cManager = new CollisionsManager(this);
		ih = InputHandler::instance();

		// Tilemap de prueba
		map = new GameObject(this);
		new MapCreator(map, "./assets/tilemaps/restaurant.tmx", sdlutils().renderer());

		test = new prueba(this);

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
	void update() {
		cManager->update();
		Scene::update();
	}
};