#include "Game.h"

#include "../Utilities/checkML.h"

Game::Game() {
	srand(time(NULL));
	sdl = SDLUtils::init("RushTaurant Secrets", 1280, 720, "assets/resources.json");
	exit = exitCoop = false;
	gameManager = GameManager::get();
	ih = InputHandler::instance();
	coop = new CoopHandler();
	sdl->showCursor();
	frameTime = 0;
}

Game::~Game() {
	delete coop;
}

void Game::init() {

}

void Game::run() {
	gameManager->initialize();

	uint32_t startTime;
	while(!exit) {
		startTime = sdlutils().currRealTime();
		
		ih->refresh();
		handleEvents();
		update();
		refresh();
		render();

		frameTime = sdlutils().currRealTime() - startTime;

		if(frameTime < FRAME_RATE) {
			SDL_Delay(FRAME_RATE - frameTime);
			frameTime = FRAME_RATE;
		}
	}
}


void Game::render() {
	sdl->clearRenderer();
	gameManager->render();
	sdl->presentRenderer();
}

void Game::update() {
	gameManager->update();
}

void Game::handleEvents() {
	if (ih->closeWindowEvent() ) {
		exit = true;
	}
	else if (ih->isKeyDown(SDLK_F11)) {
		sdl->toggleFullScreen();
	}
	else {
		gameManager->handleEvents();
	}
}

void Game::refresh() {
	gameManager->refresh();
}

void Game::runCoop() {
	uint32_t startTime;
	while(!exit && !exitCoop) {
		startTime = sdlutils().currRealTime();
		
		ih->refresh();
		coop->receive();
		handleEvents();
		update();
		refresh();
		render();

		frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < FRAME_RATE) {
			SDL_Delay(FRAME_RATE - frameTime);
			frameTime = FRAME_RATE;
		}
	}
	exitCoop = false;
}