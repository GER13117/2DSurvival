//
// Created by Okke on 27.08.2021.
//

#ifndef INC_2DSURVIVAL_TILEMAP_H
#define INC_2DSURVIVAL_TILEMAP_H

#include "Tile.h"
#include "SimplexNoise.h"

class TileMap {
private:
    sf::Vector2f tileSize;
    Tile *tile;
public:
    TileMap(float tile_size_x, float _tile_size_y, sf::Texture &texture_sheet);

    void update();

    void render();

    virtual ~TileMap();

};

#endif //INC_2DSURVIVAL_TILEMAP_H
