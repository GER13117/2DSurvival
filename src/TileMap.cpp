//
// Created by Okke on 27.08.2021.
//

#include "include/TileMap.h"

/*
TileMap::TileMap(float tile_size_x, float _tile_size_y, sf::Texture &texture_sheet) {
    this->tile = new Tile(72, 72, 36, 36, sf::Color::Red);
}*/

TileMap::TileMap(int tile_size_x, int tile_size_y) {
    float scale = 400.f;
    float offset_z = 0.05f;
    float lacunarity = 1.99f;
    float persistance = 0.5f;
    const SimplexNoise simplex(0.1f / scale, 0.5f, lacunarity,
                               persistance); // Amplitude of 0.5 for the 1st octave : sum ~1.0f
    const int octaves = static_cast<int>(3 + std::log(scale)); // Estimate number of octaves needed for the scale
    for (int x = 0; x < 100 * tile_size_x; x += tile_size_x) {
        for (int y = 0; y < tile_size_y * 100; y += tile_size_y) {
            const float noise = simplex.fractal(octaves, (float)x, (float)y) + offset_z;
            this->tile = new Tile((float)x, (float)y, (float)tile_size_x, (float)tile_size_y, tileColor(noise));
            this->tiles.push_back(this->tile);
        }
    }
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

void TileMap::update() { //check if a tile is outside the render region

}

void TileMap::render(sf::RenderTarget &target) {
    for (auto &e : this->tiles) {
        target.draw(e->getShape());
    }
}

