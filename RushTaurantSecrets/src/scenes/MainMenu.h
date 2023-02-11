#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/InputHandler.h"
#include "../../prueba.h"
class MainMenu:public Scene {
private:
	InputHandler* ih;

public:
	MainMenu():Scene() {

		ih=InputHandler::instance();
		new prueba(this);
	}

};