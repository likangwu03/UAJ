#include "Game.h"
#include "../../src/tilemap/MapCreator.h"

Game::Game() {
	sdl = SDLUtils::init("Rush Taurant Secrets", 1280, 720,"prueba.json");
	exit = false;
	sceneManager = SceneManager::instance();
	ih = InputHandler::instance();
}
void Game::run() {
	//MapCreator* map = new MapCreator("./assets/tilemaps/restaurant.tmx", sdlutils().renderer());

	uint32_t startTime, frameTime;
	while (!exit) {
		//map->render();

		startTime = sdlutils().currRealTime();  //SDL_GetTicks(); 
		ih->refresh();
		handleEvents();
		update();
		refresh();
		render();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE)
			SDL_Delay(FRAME_RATE - frameTime);
	}
	//decidir si hacer falta un bucle de juego mas precisos 
	/*
	startTime = sdlutils().currRealTime();
	while (!exit) {
		handleEvents();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			update();
			refresh();
			startTime = SDL_GetTicks();
		}
		render();
	}*/
}


void Game::render() {
	sdl->clearRenderer();
	sceneManager->render();
	sdl->presentRenderer();
}
void Game::update() {
	sceneManager->update();
}
void Game::handleEvents() {
	if (ih->closeWindowEvent()) {
		exit = true;
	}
	else {
		sceneManager->handleEvents();
	}
}

void Game::refresh() {
	sceneManager->refresh();
}