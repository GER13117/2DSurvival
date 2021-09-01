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
public:
    TileMap(int tile_size_x, int tile_size_y);

    static sf::Color tileColor(float noise);

    void update();

    void render(sf::RenderTarget &target);

    virtual ~TileMap();

};

#endif //INC_2DSURVIVAL_TILEMAP_H
