#pragma once


#include "../structure/Component.h"
class GameObject;

#include "./tmxlite/Map.hpp"
#include "../sdlutils/Texture.h"
#include <map>

using namespace tmx;
using namespace std;
using uint = unsigned int;

class MapCreator : public Component {
	constexpr static _ecs::id_type id = _ecs::cmp_MAPCREATOR;

private:
	double resizeFactor;

	SDL_Renderer* renderer;
	Map* tileMap;
	string path;
	int rows, cols, tileW, tileH;
	double tileInWindowW, tileInWindowH;
	map<uint, Texture*> tilesets;
	SDL_Texture* bg;
	Texture* testTexture;

public:
	MapCreator(GameObject* parent, const string& filePath, SDL_Renderer* renderer);
	~MapCreator();

	Map* getTileMap() { return tileMap; }
	int getRows() { return rows; }
	int getCols() { return cols; }
	int getTileW() { return tileW; }
	int getTileH() { return tileH; }
	map<uint, Texture*> getTilesets() { return tilesets; }
	SDL_Renderer* getRenderer() { return renderer; }

private:
	void loadMapDims();
	void loadTilesets();
	 void render();
};