// Proyecto2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
#include "src/structure/Game.h"
#include <iostream>

int main(int argc, char* argv[]) {
	// Check Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game* game = Game::instance();
	try {
		game->init();
		game->run();
	} catch(std::exception e) {
		std::cout << e.what();
	}
	return 0;
}