//
// Created by Okke on 27.08.2021.
//
#ifndef INC_2DSURVIVAL_TILEMAP_H
#define INC_2DSURVIVAL_TILEMAP_H

#include "Tile.h"
#include "SimplexNoise.h"
#include <vector>

class TileMap {
private:
    //std::map<std::string, Tile *> tiles;
    std::vector<Tile *> tiles;
    sf::Vector2f tileSize;
    sf::Texture textureSheet;
    Tile *tile;
    sf::Vector2i offset;
    int tileSizeX;
    int tileSizeY;
    float scale = 400.f;
    float offsetZ = 0.05f;
    float lacunarity = 1.99f;
    float persistance = 0.5f;
    SimplexNoise *simplex;
    int octaves;
    uint8_t maxTilesX;
    uint8_t maxTilesY;
    float noise;
public:
    TileMap(int tile_size_x, int tile_size_y, sf::Vector2f player_position, uint8_t max_tiles_x, uint8_t max_tiles_y);

    static sf::Color tileColor(float noise);

    void update(sf::Vector2f player_position);

    void render(sf::RenderTarget &target);

    virtual ~TileMap();
};

#endif //INC_2DSURVIVAL_TILEMAP_H