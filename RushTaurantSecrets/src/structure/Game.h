#pragma once
#include "../utils/Singleton.h"
#include "../sdlutils/SDLUtils.h"
#include "SceneManager.h"
const uint32_t FRAME_RATE = 25;  //luego a def.h


class Game:public Singleton<Game> {
private:
	SceneManager* sceneManager=nullptr;
public:
	void init();
	void run();
private:
	Game();
	void refresh();
	void render();
	void update();
	void handleEvents();
};