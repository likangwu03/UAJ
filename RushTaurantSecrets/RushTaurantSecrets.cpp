// Proyecto2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
#include "src/structure/Game.h"
#include <fstream>
#include <chrono>

int main(int argc, char* argv[]) {
	// Check Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game* game = Game::instance();
	try {
		game->init();
		game->run();
	} catch(std::exception e) {

		std::string path = std::string("crashes/") + to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
		std::ofstream file(path);
		file << "Exception caught: " << e.what();
		file.close();
	} catch(std::string str) {
		std::string path = std::string("crashes/") + to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
		std::ofstream file(path);
		file << "String caught: " << str;
		file.close();
	} catch(char* c) {
		std::string path = std::string("crashes/") + to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
		std::ofstream file(path);
		file << "Char* caught: " << c;
		file.close();
	} catch(...) {
		std::string path = std::string("crashes/") + to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
		std::ofstream file(path);
		file << "Couldn't catch anything.";
		file.close();
	}
	return 0;
}