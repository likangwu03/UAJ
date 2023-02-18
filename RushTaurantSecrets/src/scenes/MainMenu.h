#pragma once
#include "../structure/Scene.h"
#include "../../prueba.h"
#include "../../src/components/MapCreator.h"
#include "../structure/Structure_def.h"
#include "../../src/gameObjects/Client.h"
#include "../components/Image.h"
#include "../components/StraightMovement.h"
#include "../components/ClientState.h"
#include "../components/Animator.h"
#include "../structure/Food_def.h"
#include <set>
#include "../structure/CollisionsManager.h"
class MainMenu : public Scene {
private:
	CollisionsManager* cManager;
	InputHandler* ih;
	GameObject* map;
	GameObject* test;
	GameObject* player;
	GameObject* client;


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

		client = new GameObject(this);
		// Men?del día aleatorio (genera un número de platos aleatorio entre 1-5 platos, lo
		// rellena con platos diferentes entre s? y los pasa a un vector para poder acceder a ellos)
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

		GameObject* customer = new GameObject(this, _ecs::grp_CLIENTS);
		new Transform(customer, Vector(), Vector(0, 0), 50, 50);
		new Animator(customer, &((*sdl).images().at("Customer_2")), 0, 6, 1);
		float offset = 200;
		vector<Vector> points;
		points.push_back(Vector(sdl->width() / 2, sdl->height() / 2));
		points.push_back(Vector(sdl->width() / 2 + offset, sdl->height() / 2));
		points.push_back(Vector(sdl->width() / 2 + offset, sdl->height() / 2 + offset));
		points.push_back(Vector(sdl->width() / 2, sdl->height() / 2 + offset));
		new StraightMovement(customer, points, 2);*/
	}
	void update() {
		cManager->update();
		Scene::update();
	}
};