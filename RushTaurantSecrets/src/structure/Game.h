#pragma once
#include "../utils/Singleton.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "SceneManager.h"
#include "../objects/CustomerManager.h"
const uint32_t FRAME_RATE = 25;  //luego a def.h


class Game:public Singleton<Game> {
	friend Singleton<Game>;
private:
	SceneManager* sceneManager;
	InputHandler* ih;
	SDLUtils* sdl;
	bool exit;
	CustomerManager* c;
public:
	void run();
private:
	Game();
	//~Game() {};
	void refresh();
	void render();
	void update();
	void handleEvents();
	void setExit() { exit = true; }
};