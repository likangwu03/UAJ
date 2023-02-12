#pragma once

#include "./tmxlite/Map.hpp"
#include "./tmxlite/Layer.hpp"
#include "./tmxlite/TileLayer.hpp"
#include "./tmxlite/ObjectGroup.hpp"
#include "./tmxlite/Tileset.hpp"

#include "../sdlutils/Texture.h"
#include <map>

using namespace tmx;
using namespace std;
using uint = unsigned int;

class MapCreator {
private:
	SDL_Renderer* renderer;
	Map* tileMap;
	string path;
	int rows, cols, tileW, tileH;
	map<uint, Texture*> tilesets;
	SDL_Texture* bg;
	Texture* testTexture;

public:
	MapCreator(const string& filePath, SDL_Renderer* renderer);
	~MapCreator();


private:
	void loadMapDims();
	void loadMapTiles();

	void render();
};