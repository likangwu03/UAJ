#include "Game.h"
#include "../structure/Structure_def.h"

Game::Game() {
	srand(time(NULL));
	
	sdl = SDLUtils::init("Rush Taurant Secrets", 1280, 720, "assets/resources.json");
	exit = false;
	sceneManager = nullptr;
	ih = nullptr;
	sdl->showCursor();
	frameTime = 0;
}

void Game::init() {
	GameManager::init();
	sceneManager = SceneManager::instance();
	sceneManager->init();
	ih = InputHandler::instance();
}

void Game::run() {
	uint32_t startTime;
	while (!exit) {
		startTime = sdlutils().currRealTime();  //SDL_GetTicks(); 
		
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
	if (ih->closeWindowEvent() || ih->isKeyDown(SDLK_ESCAPE)) {
		exit = true;
	}
	else if (ih->isKeyDown(SDLK_F12)) {
		sdl->toggleFullScreen();
	}
	else {
		sceneManager->handleEvents();
	}
}

void Game::refresh() {
	sceneManager->refresh();
}