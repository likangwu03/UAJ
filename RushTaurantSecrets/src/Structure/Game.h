#pragma once
#include "../Utilities/Singleton.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/InputHandler.h"
#include "../Utilities/CoopHandler.h"
#include "GameManager.h"
const uint32_t FRAME_RATE = 25;  //luego a def.h

class Game : public Singleton<Game> {
	friend Singleton<Game>;
private:
	GameManager* gameManager;
	InputHandler* ih;
	CoopHandler* coop;
	SDLUtils* sdl;
	bool exit, exitCoop;
	uint32_t frameTime;
public:
	Game(Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&) = delete;
	Game& operator=(Game&&) = delete;
	~Game();
	void run();
	uint32_t& getframeTime() { return frameTime; }
	CoopHandler* getCoopHandler() { return coop; }

	void init();
	void setExitCoop() { exitCoop = true; coop->closeConnection(); }
	void runCoop();
private:
	Game();
	void refresh();
	void render();
	void update();
	void handleEvents();
	void setExit() { exit = true; }

};