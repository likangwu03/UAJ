#pragma once
#include "../structure/Scene.h"
#include "../../prueba.h"
#include "../../src/components/MapCreator.h"

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

		//map = new GameObject(this);
		//MapCreator* mpCrt = new MapCreator(map, "./assets/tilemaps/test.tmx", sdlutils().renderer());

		this->addObject(test, 0);
	}
	virtual void handleEvents();	
};