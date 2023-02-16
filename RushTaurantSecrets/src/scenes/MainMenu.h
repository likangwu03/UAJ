#pragma once
#include "../structure/Scene.h"
#include "../../prueba.h"
#include "../../src/components/MapCreator.h"
#include "../structure/Structure_def.h"

#include "../components/ClientState.h"
#include "../components/ClientInTableState.h"

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

		map = new GameObject(this);
		new MapCreator(map, "./assets/tilemaps/restaurant.tmx", sdlutils().renderer());
		test = new prueba(this);
		
		client = new GameObject(this);
		ClientState* clSt = new ClientState(client);
		new ClientInTableState(client, clSt);

		
		
	}
};