#pragma once
#include "../structure/Scene.h"
#include "../../prueba.h"
#include "../../src/components/MapCreator.h"
#include "../structure/Structure_def.h"

#include "../components/ClientState.h"
#include "../structure/Food_def.h"
#include <set>
class MainMenu : public Scene {
private:
	InputHandler* ih;
	GameObject* map;
	GameObject* test;
	GameObject* player;
	GameObject* client;

public:
	MainMenu() : Scene() {

		ih = InputHandler::instance();

		// Tilemap de prueba
		map = new GameObject(this);
		new MapCreator(map, "./assets/tilemaps/restaurant.tmx", sdlutils().renderer());
		

		test = new prueba(this);

		
		client = new GameObject(this);
		// Menú del día aleatorio (genera un número de platos aleatorio entre 1-5 platos, lo
		// rellena con platos diferentes entre sí, y los pasa a un vector para poder acceder a ellos)
		set<int> aux;
		int auxSize = rand() % 5 + 1;
		for (int i = 0; i < auxSize; i++) {
			if (!aux.insert(rand() % _ecs::NONE_DISH).second)
				i--;
		}
		vector<int> menu;
		for (auto i = aux.begin(); i != aux.end(); ++i) menu.push_back(*i);

		new ClientState(client, menu);
		
		
	}
};