#include <fstream>
#include "Map.h"
#include "./Game.h"
#include "./EntityManager.h"
#include "./components/TileComponent.h"

extern EntityManager manager;

Map::Map(std::string textureId, int scale, int tileSize) {
    this->textureId = textureId;
    this->scale = scale;
    this->tileSize = tileSize;
}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY) {
    std::fstream mapFile;
    mapFile.open(filePath);

    for (int y = 0; y < mapSizeY; y++) {
        for (int x = 0; x < mapSizeX; x++) {
            char ch;
            mapFile.get(ch);
            int srcRectY = atoi(&ch) * tileSize;
            mapFile.get(ch);
            int srcRectX = atoi(&ch) * tileSize;
            AddTile(srcRectX, srcRectY, x * (scale * tileSize), y * (scale * tileSize));
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Map::AddTile(int srcRectX, int srcRectY, int x, int y) {
    Entity& newTile(manager.AddEntity("Tile", TILEMAP_LAYER));
    newTile.AddComponent<TileComponent>(srcRectX, srcRectY, x, y, this->tileSize,this->scale, this->textureId);
}