//
// Created by Okke on 27.08.2021.
//

#include "include/TileMap.h"

TileMap::TileMap(int tile_size_x, int tile_size_y, sf::Vector2f player_position, uint8_t max_tiles_x,
                 uint8_t max_tiles_y) {
    this->offset = static_cast<sf::Vector2i>(player_position);
    this->tileSizeX = tile_size_x;
    this->tileSizeY = tile_size_y;
    this->maxTilesX = max_tiles_x;
    this->maxTilesY = max_tiles_y;
    this->globalScale = 800.f; //Scale for generating continents
    this->grasScale = 70.f;
    this->offsetZ = 0.05f;
    this->lacunarity = 1.99f;
    this->persistance = 0.5f;
    this->globalSimplex = new SimplexNoise(0.1f / globalScale, 0.5f, lacunarity,
                                           persistance); // Amplitude of 0.5 for the 1st octave : sum ~1.0f
    this->grasSimplex = new SimplexNoise(0.1f / grasScale, 0.5f, lacunarity, persistance);
    this->octaves = static_cast<int>(3 + std::log(globalScale)); // Estimate number of octaves needed for the scale

    /**
     * This loop draws tiles on the whole screen when the Tilemap is created. In "update" tiles get appended or removed.
     */
    for (int x = offset.x - maxTilesX * tileSizeX; x < maxTilesX * tileSizeX + offset.x; x += tileSizeX) {
        for (int y = offset.y - maxTilesY * tileSizeY; y < maxTilesY * tileSizeY + offset.y; y += tileSizeY) {
            this->tile = new Tile((float) x,
                                  (float) y,
                                  (float) tileSizeX,
                                  (float) tileSizeY,
                                  tileColor(
                                          this->globalSimplex->fractal(octaves, (float) x, (float) y) + offsetZ,
                                          this->grasSimplex->fractal(octaves, (float) x + 9129834.f,
                                                                     (float) y + 1208012.f) + offsetZ));
            this->tiles.push_back(this->tile);
        }
    }
}


TileMap::~TileMap() {

}

//TODO: return textures instead
//TODO: create Spritesheet
//TODO: include AnimationComponent
sf::Color TileMap::tileColor(float noise, float grasNoise) {
    if (noise < -0.500f) {
        return {2, 43, 68}; // dark blue: deep water
    } else if (noise < -0.10f) {
        return {9, 62, 92}; // deep blue: water
    } else if (noise < -0.060f) {
        return {69, 108, 118}; // blue: shallow water
    } else if (noise < 0.010f) {
        return {207, 209, 134}; // Beach
    } else if (noise < 0.60f) { // grass
        if (grasNoise < 0.f)
            return {71, 117, 20};
        else if (grasNoise < 0.5f)
            return {94, 135, 50};
        else
            return {105, 138, 70};
    } else if (noise < 0.700f) {
        return {115, 128, 77}; // light green: veld
    } else if (noise < 0.900f) {
        return {153, 143, 92}; // brown: tundra
    } else {
        return {179, 179, 179}; // grey: rocks
    }
}



//TODO: make code more beautiful
//TODO: maybe only update the map if the player is moving?
/**
 * removes and appends tiles from the tiles vector by checking if its position is within the screen.
 * @param player_position positon of the player, is used to calculate the offset from 0,0 rounded by the size of a tile.
 */
void TileMap::update(sf::Vector2f player_position) {
    offset.x = ((int) (player_position.x / (float) tileSizeX) * tileSizeX);
    offset.y = ((int) (player_position.y / (float) tileSizeY) * tileSizeY);

    for (it = tiles.begin(); it != tiles.end();) {
        if ((*it)->getShape().getPosition().x + tileSizeX > offset.x + maxTilesX * tileSizeX) {
            tileX = (*it)->getShape().getPosition().x - (2 * maxTilesX * tileSizeX);
            tileY = (*it)->getShape().getPosition().y;
            tiles.push_back(new Tile(tileX, tileY, tileSizeX, tileSizeY,
                                     tileColor(
                                             this->globalSimplex->fractal(octaves, tileX, tileY) + offsetZ,
                                             this->grasSimplex->fractal(octaves, tileX + 9129834.f, tileY + 1208012.f) +
                                             offsetZ)));
            delete *it;
            it = tiles.erase(it);
        } else if ((*it)->getShape().getPosition().x < offset.x - maxTilesX * tileSizeX) {
            tileX = (*it)->getShape().getPosition().x + (2 * maxTilesX * tileSizeX);
            tileY = (*it)->getShape().getPosition().y;
            tiles.push_back(new Tile(tileX, tileY, tileSizeX, tileSizeY,
                                     tileColor(
                                             this->globalSimplex->fractal(octaves, tileX, tileY) + offsetZ,
                                             this->grasSimplex->fractal(octaves, tileX + 9129834.f, tileY + 1208012.f) +
                                             offsetZ)));
            delete *it;
            it = tiles.erase(it);
        } else if ((*it)->getShape().getPosition().y + tileSizeY > offset.y + maxTilesY * tileSizeY) {
            tileX = (*it)->getShape().getPosition().x;
            tileY = (*it)->getShape().getPosition().y - (2 * maxTilesY * tileSizeY);
            tiles.push_back(new Tile(tileX, tileY, tileSizeX, tileSizeY,
                                     tileColor(
                                             this->globalSimplex->fractal(octaves, tileX, tileY) + offsetZ,
                                             this->grasSimplex->fractal(octaves, tileX + 9129834.f, tileY + 1208012.f) +
                                             offsetZ)));
            delete *it;
            it = tiles.erase(it);
        } else if ((*it)->getShape().getPosition().y < offset.y - maxTilesY * tileSizeY) {
            tileX = (*it)->getShape().getPosition().x;
            tileY = (*it)->getShape().getPosition().y + (2 * maxTilesY * tileSizeY);
            tiles.push_back(new Tile(tileX, tileY, tileSizeX, tileSizeY,
                                     tileColor(
                                             this->globalSimplex->fractal(octaves, tileX, tileY) + offsetZ,
                                             this->grasSimplex->fractal(octaves, tileX + 9129834.f, tileY + 1208012.f) +
                                             offsetZ)));
            delete *it;
            it = tiles.erase(it);
        } else {
            ++it;
        }
    }
    //std::cout << tiles.size() << std::endl;
    /*
    for (auto e: tiles) {
        delete e;
    }
    this->tiles.clear();

    for (int x = offset.x - maxTilesX * tileSizeX; x < maxTilesX * tileSizeX + offset.x; x += tileSizeX) {
        for (int y = offset.y - maxTilesY * tileSizeY; y < maxTilesY * tileSizeY + offset.y; y += tileSizeY) {
            this->tile = new Tile((float) x, (float) y, (float) tileSizeX, (float) tileSizeY,
                                  tileColor(this->globalSimplex->fractal(octaves, (float) x, (float) y) + offsetZ,
                                            this->grasSimplex->fractal(octaves, (float) x + 9129834.f,
                                                                       (float) y + 1208012.f) + offsetZ));
            this->tiles.push_back(this->tile);
        }
    }*/
}

void TileMap::render(sf::RenderTarget &target) {
    for (auto &e: this->tiles) {
        target.draw(e->getShape());
    }
}