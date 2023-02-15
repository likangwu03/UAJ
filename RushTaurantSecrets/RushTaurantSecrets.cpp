//// Proyecto2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
////
//
//#include <SDL.h>
//#include <iostream>
//#include <SDL_image.h>
////#include <SDL_ttf.h>
////#include <box2d/b2_collision.h>
// 
//
//using namespace std;
//
//using uint = unsigned int;
//
//void firstTest() {
//	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
//	SDL_Window* window = nullptr;
//	SDL_Renderer* renderer = nullptr;
//	const uint winWidth = 800;
//	const uint winHeight = 600;
//	SDL_
// (SDL_INIT_EVERYTHING);
//	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
//		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
//	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//	if (window == nullptr || renderer == nullptr)
//		cout << "Error cargando SDL" << endl;
//	else {
//		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//		SDL_RenderClear(renderer);
//		SDL_RenderPresent(renderer);
//		SDL_Delay(5000);
//	}
//
//
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//}
//
//int main(int argc, char* argv[]) {
//	// Check Memory Leaks
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//
//
//	firstTest();
//	return 0;
//}
#include "src/structure/Game.h"

int main(int argc, char* argv[]) {
		// Check Memory Leaks
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		Game* game = Game::instance();
		game->run();
		return 0;
	}