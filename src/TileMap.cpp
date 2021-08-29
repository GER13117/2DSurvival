//
// Created by Okke on 27.08.2021.
//

#include "include/TileMap.h"

/*
TileMap::TileMap::TileMap(float tile_size_x, float _tile_size_y, sf::Texture &texture_sheet) {
    this->tile = new Tile(72, 72, 36, 36, sf::Color::Red);
}*/

TileMap::TileMap(float tile_size_x, float tile_size_y) {
    for (int x = 0; x < 20; ++x) {
        for (int y = 0; y < 20; ++y) {
            this->tile = new Tile(x * tile_size_x, y * tile_size_y, tile_size_x, tile_size_y, tileColor(x, y));
            this->tiles.push_back(this->tile);
        }
    }
}


TileMap::~TileMap() {

}

sf::Color TileMap::tileColor(int x,
                             int y) {  //Will return a texture instead of a color later on, and use the noise to determine the texture
    if (x % 2 == y % 2)
        return sf::Color::White;
    else if (x % 2 != y % 2)
        return sf::Color::Black;

    return sf::Color::Green;
}

void TileMap::update() { //check if a tile is outside the render region

}

void TileMap::render(sf::RenderTarget &target) {
    for (auto &e : this->tiles) {
        target.draw(e->getShape());
    }
}

