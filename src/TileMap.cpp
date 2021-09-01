//
// Created by Okke on 27.08.2021.
//

#include "include/TileMap.h"

/*
TileMap::TileMap(float tile_size_x, float _tile_size_y, sf::Texture &texture_sheet) {
    this->tile = new Tile(72, 72, 36, 36, sf::Color::Red);
}*/

TileMap::TileMap(int tile_size_x, int tile_size_y, sf::Vector2f player_position, uint8_t max_tiles_x,
                 uint8_t max_tiles_y) {
    this->playerPosition = player_position;
    this->tileSizeX = tile_size_x;
    this->tileSizeY = tile_size_y;
    this->maxTilesX = max_tiles_x;
    this->maxTilesY = max_tiles_y;
    this->scale = 400.f;
    this->offsetZ = 0.05f;
    this->lacunarity = 1.99f;
    this->persistance = 0.5f;
    simplex = new SimplexNoise(0.1f / scale, 0.5f, lacunarity,
                               persistance); // Amplitude of 0.5 for the 1st octave : sum ~1.0f
    this->octaves = static_cast<int>(3 + std::log(scale)); // Estimate number of octaves needed for the scale
}


TileMap::~TileMap() {

}

sf::Color TileMap::tileColor(
        float noise) {  //Will return a texture instead of a color later on, and use the noise to determine the texture
    //sf::Color(255, 255, 255); // white: snow

    if (noise < -0.500f) {
        return {2, 43, 68}; // dark blue: deep water
    } else if (noise < -0.10f) {
        return {9, 62, 92}; // deep blue: water
    } else if (noise < -0.060f) {
        return {69, 108, 118}; // blue: shallow water
    } else if (noise < 0.010f) {
        return {244, 247, 153}; // Beach
    } else if (noise < 0.60f) {
        return {42, 102, 41}; // green: grass
    } else if (noise < 0.700f) {
        return {115, 128, 77}; // light green: veld
    } else if (noise < 0.900f) {
        return {153, 143, 92}; // brown: tundra
    } else {
        return {179, 179, 179}; // grey: rocks
    }
    //return sf::Color::Green;
}

void TileMap::update(sf::Vector2f player_position) { //check if a tile is outside the render region
    for (int x = 0; x < maxTilesX * tileSizeX; x += tileSizeX) {
        for (int y = 0; y < maxTilesY * tileSizeY; y += tileSizeY) { //TODO: Das Spiel malt jetzt immer wieder neue Tiles obwohl es nicht nötig ist --> gucken ob an einer bestimmten Stelle schon ein Tiles ist, wenn ja nicht neu zeichnen.
            noise = simplex->fractal(octaves, (float) x, (float) y) + offsetZ; //TODO: Wenn die Tiles außerhalb das Bildschirms sind, sollen sie nicht mehr gezeichnet und aus dem Vector der Tiles gelöscht werden.
            this->tile = new Tile((float) x, (float) y, (float) tileSizeX, (float) tileSizeY, tileColor(noise));
            this->tiles.push_back(this->tile);
        }
    }
    /*for (int i = 0; i <= this->tiles.size(); i++) {
        if (this->tiles[i]->getShape().getPosition().x - player_position.x > tileSizeX * maxTilesX &&
                this->tiles[i]->getShape().getPosition().y - player_position.y > tileSizeY * maxTilesY) {
            this->tiles.erase(this->tiles.begin() + i);
        }
    }*/
}

void TileMap::render(sf::RenderTarget &target) {
    for (auto &e: this->tiles) {
        target.draw(e->getShape());
    }
}

