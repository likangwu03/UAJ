#pragma once
#include "../utils/Singleton.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "GameManager.h"
const uint32_t FRAME_RATE = 25;  //luego a def.h

class Game : public Singleton<Game> {
	friend Singleton<Game>;
private:
	GameManager* gameManager;
	InputHandler* ih;
	SDLUtils* sdl;
	bool exit;
	uint32_t frameTime;
public:
	Game(Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&) = delete;
	Game& operator=(Game&&) = delete;
	void run();
	uint32_t& getframeTime() { return frameTime; }

	void init();
private:
	Game();
	void refresh();
	void render();
	void update();
	void handleEvents();
	void setExit() { exit = true; }
};