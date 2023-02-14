#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/InputHandler.h"
#include "../../prueba.h"

#include "../../src/components/MapCreator.h"


class MainMenu : public Scene {
private:
	InputHandler* ih;
	GameObject* map;
	GameObject* test;

public:
	MainMenu() : Scene() {

		ih = InputHandler::instance();
		test = new prueba(this);

		//map = new GameObject(this);
		//MapCreator* mpCrt = new MapCreator(map, "./assets/tilemaps/test.tmx", sdlutils().renderer());
	}
	virtual void handleEvents();
	
};