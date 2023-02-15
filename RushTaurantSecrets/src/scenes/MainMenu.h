#pragma once
#include "../structure/Scene.h"
#include "../../prueba.h"
#include "../../src/components/MapCreator.h"
#include "../structure/Structure_def.h"

class MainMenu : public Scene {
private:
	InputHandler* ih;
	GameObject* map;
	GameObject* test;
	GameObject* player;

public:
	MainMenu() : Scene() {

		ih = InputHandler::instance();
		test = new prueba(this);

		
		map = new GameObject(this, _ecs::hdr_PRUEBA);
		MapCreator* mpCrt = new MapCreator(map, "./assets/tilemaps/restaurant.tmx", sdlutils().renderer());
		
		
		
		//this->addObject(test, 0);
	}
};