#include "Game.h"

Game::Game() {
	sceneManager = SceneManager::instance();
}
void Game::init() {
	sdlutils().init("Rush Taurant Secrets", 1280, 720);
	
}

void Game::run() {
	uint32_t startTime, frameTime;
	bool exit = false;

	while (!exit) { 
		startTime = sdlutils().currRealTime();  //SDL_GetTicks(); 
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
	sceneManager->render();
}
void Game::update() {
	sceneManager->update();
}
void Game::handleEvents() {
	sceneManager->handleEvents();
}

void Game::refresh() {
	sceneManager->refresh();
}