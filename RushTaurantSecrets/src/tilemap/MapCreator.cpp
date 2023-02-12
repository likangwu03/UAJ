#include "MapCreator.h"



MapCreator::MapCreator(const string& filePath, SDL_Renderer* renderer) : path(filePath), renderer(renderer) {
    loadMapDims();
    loadMapTiles();
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
    rows = tileCount.x;
    cols = tileCount.y;

    // Lee el tamaño de los tiles
    auto tileSize = tileMap->getTileSize();
    tileW = tileSize.x;
    tileH = tileSize.y;

    // Calcula las dimensiones totales del mapa y asigna a la
    // textura del mapa una textura con dichas dimensiones
    int width = rows * tileW;
    int height = cols * tileH;
    bg = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

    testTexture = new Texture(renderer, "../../assets/LimeZu_modern_interiors/Gif_exterior_pack/atlas.png");
}


void MapCreator::loadMapTiles() {
    SDL_RenderClear(renderer);
    SDL_SetTextureBlendMode(bg, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, bg);

    // Lee los tilesets del tilemap y los recorre
    auto mapTileSets = tileMap->getTilesets();
    for (auto& ts : mapTileSets) {
        // Lee la ID del tileset, la convierte a uint y busca su textura
        uint tilesetID = stoul(ts.getName());
        Texture* tileTexture = testTexture;
            //tilesets.find(tilesetID)->second;

        tilesets.insert({ts.getFirstGID(), tileTexture });
    }

}
