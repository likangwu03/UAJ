#include "Game.h"
#include "../structure/Structure_def.h"

Game::Game() {
	sdl = SDLUtils::init("Rush Taurant Secrets", 1280, 720, "assets/resources.json");
	exit = false;
	sceneManager = SceneManager::instance();
	ih = InputHandler::instance();
	sdl->showCursor();
}

void Game::run() {
	uint32_t startTime, frameTime;
	while (!exit) {
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
	SDL_Rect destRect;
	destRect.x = 600;
	destRect.y = 600;
	destRect.w = 100;
	destRect.h = 100;
	sceneManager->render();
	sdl->presentRenderer();
}
void Game::update() {
	sceneManager->update();
}
void Game::handleEvents() {
	if (ih->closeWindowEvent() || ih->isKeyDown(SDLK_ESCAPE)) {
		exit = true;
	}
	else {
		sceneManager->handleEvents();
	}
}

void Game::refresh() {
	sceneManager->refresh();
}