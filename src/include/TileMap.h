//
// Created by Okke on 27.08.2021.
//

#ifndef INC_2DSURVIVAL_TILEMAP_H
#define INC_2DSURVIVAL_TILEMAP_H

#include "Tile.h"


class TileMap {
private:
    sf::Vector2f size;
public:
    TileMap();

    virtual ~TileMap();

};

TileMap::~TileMap() {

}


#endif //INC_2DSURVIVAL_TILEMAP_H
