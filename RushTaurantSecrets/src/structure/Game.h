#pragma once
#include "../utils/Singleton.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "SceneManager.h"
#include "GameInfor.h"
const uint32_t FRAME_RATE = 25;  //luego a def.h


class Game : public Singleton<Game> {
	friend Singleton<Game>;
private:
	SceneManager* sceneManager;
	InputHandler* ih;
	SDLUtils* sdl;
	bool exit;
public:
	Game(Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&) = delete;
	Game& operator=(Game&&) = delete;
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