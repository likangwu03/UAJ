#include "Game.h"

#include "../utils/checkML.h"

Game::Game() {
	srand(time(NULL));
	
	sdl = SDLUtils::init("Rush Taurant Secrets", 1280, 720, "assets/resources.json");
	exit = false;
	gameManager = GameManager::instance();
	ih = InputHandler::instance();
	sdl->showCursor();
	frameTime = 0;
}

void Game::init() {
}

void Game::run() {
	gameManager->initialize();

	uint32_t startTime;
	while (!exit) {
		startTime = sdlutils().currRealTime();
		
		ih->refresh();
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
	if (ih->closeWindowEvent() || ih->isKeyDown(SDLK_ESCAPE)) {
		exit = true;
	}
	else if (ih->isKeyDown(SDLK_F12)) {
		sdl->toggleFullScreen();
	}
	else {
		gameManager->handleEvents();
	}
}

void Game::refresh() {
	gameManager->refresh();
}