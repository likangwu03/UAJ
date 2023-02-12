#include "MapCreator.h"



MapCreator::MapCreator(const string& filePath, SDL_Renderer* renderer) : path(filePath), renderer(renderer) {
    loadMapDims();

    SDL_RenderClear(renderer);
    SDL_SetTextureBlendMode(bg, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, bg);

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



    testTexture = new Texture(renderer, "./assets/Gif_exterior_pack/atlas.png");
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

            int tilesetID = -2;
            // Se recorre todo el mapa 
            for (int rw = 0; rw < rows; ++rw) {
                // Además, si no existe tileset para el tile, pasa a la siguiente casilla
                for (int cl = 0; cl < cols && tilesetID != -1; ++cols) {
                    tilesetID = -2;

                    // Se obtiene la ID del tile en su tileset y se
                    // usa para obtener la ID del tile en todo el mapa
                    int tileIDInTileset = cl + rw * cols;
                    int tileID = tiles[tileIDInTileset].ID;

                    // Si la casilla no está vacía
                    if (tileID != 0) {
                        // Recorre los tilesets cargados y busca el primero que
                        // el ID más cercano y <= al ID del tile
                        int tilesetFile = 0;
                        bool found = false;
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

                            // Se calcula la zona del tileset en la que está el tile a dibujar
                            int tilesetRegionX = (tileID % (tilesetW / tileW)) * tileW;
                            int tilesetRegionY = (tileID / (tilesetH / tileH)) * tileH;

                            // Se calcula la posición en la que dibujar el tile
                            int tileX = cl * tileW;
                            int tileY = rw * tileH;

                            // Tile del tileset
                            SDL_Rect srcRect = { tilesetRegionX, tilesetRegionY, tileW, tileH };
                            // Parte del mapa en el que se va a dibujar el tile
                            SDL_Rect destRect = { tileX, tileY, srcRect.w, srcRect.h };

                            // Correción por rotación
                            double rotation = tiles[tileIDInTileset].flipFlags;
                            float rotationCorrection = 45;
                            SDL_RendererFlip tileFlip = SDL_FLIP_NONE;

                            // Dibuja el el tile del tileset (tilesets[tilesetID) srcRect en la posición destRect
                            tilesets[tilesetID]->render(srcRect, destRect, rotation * rotationCorrection, nullptr, tileFlip);
                        }
                    }

                }
            }
        }
    }
    SDL_SetRenderTarget(renderer, nullptr);

}