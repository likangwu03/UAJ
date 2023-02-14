#include "MapCreator.h"
#include "../structure/Structure_def.h"

#include "./tmxlite/Layer.hpp"
#include "./tmxlite/TileLayer.hpp"
#include "./tmxlite/ObjectGroup.hpp"
#include "./tmxlite/Tileset.hpp"

MapCreator::MapCreator(GameObject* parent, const string& filePath, SDL_Renderer* renderer) : Component(parent, id), path(filePath), renderer(renderer) {
    resizeFactor = 0.5;

    loadMapDims();

    SDL_RenderClear(renderer);
    SDL_SetTextureBlendMode(bg, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, bg);
    
    tileInWindowW = tileW * resizeFactor;
    tileInWindowH = tileH * resizeFactor;

    loadTilesets();
}

MapCreator::~MapCreator() {
    if (tileMap != nullptr) delete tileMap;
    delete testTexture;
}


void MapCreator::loadMapDims() {
    // Carga el tilemap
    tileMap = new Map();
    tileMap->load(path);

    // Cuenta las filas y columnas que tiene
    auto tileCount = tileMap->getTileCount();
    rows = tileCount.y;
    cols = tileCount.x;

    // Lee el tamaño de los tiles
    auto tileSize = tileMap->getTileSize();
    tileW = tileSize.x;
    tileH = tileSize.y;

    // Calcula las dimensiones totales del mapa y asigna a la
    // textura del mapa una textura con dichas dimensiones
    int width = cols * tileW;
    int height = rows * tileH;
    bg = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);



    testTexture = new Texture(renderer, "assets/Sprites/Restaurant/atlas.png");
}


void MapCreator::loadTilesets() {
    // Lee los tilesets del tilemap y los recorre
    auto mapTileSets = tileMap->getTilesets();
    for (auto& ts : mapTileSets) {
        // Lee la ID del tileset, la convierte a uint y busca su textura precargada
        string tilesetID = ts.getName();
        Texture* tileTexture = testTexture;
            //tilesets.find(tilesetID)->second;

        // Guarda la textura precargada en los tilesets del mapa
        tilesets.insert({ts.getFirstGID(), tileTexture });
    }

}


void MapCreator::render() {
    // Lee las capas del tilemap y las recorre
    auto& layers = tileMap->getLayers();
    for (auto& ly : layers) {
        // Si el tipo de la capa es de tiles
        if (ly->getType() == Layer::Type::Tile) {
            // Se carga la capa y se leen sus tiles
            TileLayer* tileLayer = dynamic_cast<TileLayer*>(ly.get());
            auto& tiles = tileLayer->getTiles();

            bool found = false;
            // Se recorre todo el mapa 
            for (int rw = 0; rw < rows; rw++) {
                // Además, si no existe tileset para el tile, pasa a la siguiente casilla
                for (int cl = 0; cl < cols && !found; cl++) {
                    found = false;
                    // Se obtiene la ID del tile en el mapa y se
                    // usa para obtener la ID del tile en el tileset
                    int tileInTilemap = cl + rw * cols;
                    int tileID = tiles[tileInTilemap].ID;

                    // Si la casilla no está vacía
                    if (tileID != 0) {
                        // Recorre los tilesets cargados y busca el primero que
                        // el ID más cercano y <= al ID del tile
                        int tilesetFile = 0, tilesetID = -1;
                        for (auto ts = tilesets.begin(); ts != tilesets.end() && !found; ++ts) {
                            if (ts->first <= tileID) {
                                tilesetID = ts->first;
                                tilesetFile++;
                            }
                            else found = true;
                        }

                        // Si se encuentra el tileset que contiene el tile
                        if (tilesetID != -1) {
                            // Se normaliza el índice
                            tileID -= tilesetID;

                            // Se calculan las dimensiones del tileset
                            int tilesetW = 0, tilesetH = 0;
                            SDL_QueryTexture(tilesets[tilesetID]->getTexture(), NULL, NULL, &tilesetW, &tilesetH);
                            int tilesetCols = tilesetW / tileW;
                            int tilesetRows = tilesetH / tileH;

                            // Se calcula la zona del tileset en la que está el tile a dibujar
                            int tilesetRegionX = (tileID % tilesetCols) * tileW;
                            int tilesetRegionY = (tileID / tilesetCols) * tileH;


                            // Se calcula la posición en la que dibujar el tile
                            int tileX = cl * tileInWindowW;
                            int tileY = rw * tileInWindowH;

                            // Tile del tileset
                            SDL_Rect srcRect = { tilesetRegionX, tilesetRegionY, tileW, tileH };
                            // Parte del mapa en el que se va a dibujar el tile
                            SDL_Rect destRect = { tileX, tileY, tileInWindowW, tileInWindowH };

                            // Dibuja el el tile del tileset (tilesets[tilesetID) srcRect en la posición destRect
                            tilesets[tilesetID]->render(srcRect, destRect);

                        }
                    }

                }
            }
        }
    }
    SDL_SetRenderTarget(renderer, nullptr);
};