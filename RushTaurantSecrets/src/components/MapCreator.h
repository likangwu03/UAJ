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
	constexpr static _ecs::_cmp_id id = _ecs::cmp_MAPCREATOR;

private:
	double resizeFactor;

	SDL_Renderer* renderer;
	Map* tileMap;
	string path;
	int rows, cols, tileW, tileH;
	double tileInWindowW, tileInWindowH;
	map<uint, Texture*> tilesets;
	SDL_Texture* bg;

public:
	MapCreator(GameObject* parent, const string& filePath, SDL_Renderer* renderer);
	~MapCreator();

private:
	void loadMapDims();
	void loadTilesets();
	void render();
};