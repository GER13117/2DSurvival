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
    this->geologicalScale = 800.f; //Scale for generating continents
    this->grasScale = 70.f;
    this->temperatureScale = 2000.f;
    this->humidityScale = 2000.f;
    this->offsetZ = 0.05f;
    this->lacunarity = 1.99f;
    this->persistance = 0.5f;
    this->geologicalSimplex = new SimplexNoise(0.1f / geologicalScale, 0.5f, lacunarity,
                                               persistance); // Amplitude of 0.5 for the 1st octave : sum ~1.0f
    this->grasSimplex = new SimplexNoise(0.1f / grasScale, 0.5f, lacunarity, persistance);
    this->humidity = new SimplexNoise(0.1f / humidityScale, 0.5f, lacunarity, persistance);
    this->temperature = new SimplexNoise(0.1f / temperatureScale, 2.f, lacunarity, persistance);
    this->octaves = static_cast<int>(3 + std::log(geologicalScale)); // Estimate number of octaves needed for the scale

    /**
     * This loop draws tiles on the whole screen when the Tilemap is created. In "update" tiles get appended or removed.
     */
    for (int x = offset.x - maxTilesX * tileSizeX; x < maxTilesX * tileSizeX + offset.x; x += tileSizeX) {
        for (int y = offset.y - maxTilesY * tileSizeY; y < maxTilesY * tileSizeY + offset.y; y += tileSizeY) {
            this->tile = new Tile(sf::Vector2f{(float) x, (float) y},
                                  sf::Vector2f{(float) tileSizeX, (float) tileSizeY},
                                  tileColor(
                                          this->geologicalSimplex->fractal(octaves, (float) x, (float) y) + offsetZ,
                                          this->grasSimplex->fractal(octaves, (float) x + 9129834.f, (float) y + 1208012.f),
                                          this->temperature->fractal(octaves, (float) x, (float) y),
                                          this->humidity->fractal(octaves, (float) x, (float) y)));
            this->tiles.push_back(this->tile);
        }
    }
}


TileMap::~TileMap() {
    for (auto e: tiles) {
        delete e;
    }
    this->tiles.clear();
    for (auto e: structures) {
        delete e;
    }
    this->structures.clear();
}

void TileMap::getStructuresInScreenSpace(sf::Vector2i view_offset, sf::Vector2f player_position) { //TODO: Fix memory leak
    for (auto i: structures) {
        if (i->getShape().getPosition().x > view_offset.x + maxTilesX * tileSizeX || i->getShape().getPosition().x < view_offset.x - maxTilesX * tileSizeX ||
            i->getShape().getPosition().y > view_offset.y + maxTilesX * tileSizeX || i->getShape().getPosition().y < view_offset.y - maxTilesX * tileSizeX)
            continue;
        else
            structuresInScreen.push_back(i);
    }
}

sf::Color TileMap::rainForest(float noise, float textureVarNoise) {
    std::cout << "rainForest" << std::endl;
    if (noise < -0.500f) {
        return {2, 43, 68}; // dark blue: deep water
    } else if (noise < -0.10f) {
        return {9, 62, 92}; // deep blue: water
    } else if (noise < -0.060f) {
        return {69, 108, 118}; // blue: shallow water
    } else if (noise < 0.010f) {
        return {207, 209, 134}; // Beach
    } else {
        if (textureVarNoise < 0.f)
            return {71, 117, 20};
        else if (textureVarNoise < 0.5f)
            return {94, 135, 50};
        else
            return {105, 138, 70};
    }
}

sf::Color TileMap::tundra(float noise, float textureVarNoise) {
    std::cout << "Tundra" << std::endl;
    if (noise < -0.500f) {
        return {2, 43, 68}; // dark blue: deep water
    } else if (noise < -0.10f) {
        return {9, 62, 92}; // deep blue: water
    } else if (noise < -0.060f) {
        return {91, 130, 140}; // blue: shallow water
    } else if (noise < 0.010f) {
        return {224, 196, 150}; // Beach
    } else if (noise < 0.8f) {
        if (textureVarNoise < 0.f)
            return {115, 106, 21};
        else if (textureVarNoise < 0.3f)
            return {155, 139, 0};
        else if (textureVarNoise < 0.6f)
            return {137, 115, 1};
        else
            return {88, 91, 7};
    } else
        return {107, 101, 89}; // TODO: Variation noise
}

sf::Color TileMap::swamp(float noise, float textureVarNoise) {
    std::cout << "swamp" << std::endl;
    if (noise < -0.500f) {
        return {2, 43, 68}; // dark blue: deep water
    } else if (noise < -0.10f) {
        return {9, 62, 92}; // deep blue: water
    } else if (noise < -0.060f) {
        return {69, 108, 118}; // blue: shallow water
    } else if (noise < 0.010f) {
        return {207, 209, 134}; // Beach
    } else {
        if (textureVarNoise < 0.f)
            return {71, 117, 20};
        else if (textureVarNoise < 0.5f)
            return {94, 135, 50};
        else
            return {105, 138, 70};
    }
}

sf::Color TileMap::taiga(float noise, float textureVarNoise) {
    std::cout << "taiga" << std::endl;
    if (noise < -0.500f) {
        return {55, 74, 110}; // dark blue: deep water
    } else if (noise < -0.10f) {
        return {113, 127, 153}; // deep blue: water
    } else if (noise < -0.060f) {
        return {141, 154, 179}; // blue: shallow water
    } else if (noise < 0.010f) {
        return {128, 125, 111}; // Beach
    } else {
        if (textureVarNoise < 0.f)
            return {147, 140, 103};
        else if (textureVarNoise < 0.3f)
            return {153, 116, 78};
        else if (textureVarNoise < 0.6f)
            return {135, 119, 76};
        else
            return {177, 136, 91};
    }
}

sf::Color TileMap::saisonalForest(float noise, float textureVarNoise) {
    std::cout << "saisonal forest" << std::endl;
    if (noise < -0.500f) {
        return {2, 43, 68}; // dark blue: deep water
    } else if (noise < -0.10f) {
        return {9, 62, 92}; // deep blue: water
    } else if (noise < -0.060f) {
        return {69, 108, 118}; // blue: shallow water
    } else if (noise < 0.010f) {
        return {207, 209, 134}; // Beach
    } else {
        if (textureVarNoise < 0.f)
            return {71, 117, 20};
        else if (textureVarNoise < 0.5f)
            return {94, 135, 50};
        else
            return {105, 138, 70};
    }
}

sf::Color TileMap::thickForest(float noise, float textureVarNoise) {
    std::cout << "Thick forest" << std::endl;
    if (noise < -0.500f) {
        return {2, 43, 68}; // dark blue: deep water
    } else if (noise < -0.10f) {
        return {9, 62, 92}; // deep blue: water
    } else if (noise < -0.060f) {
        return {69, 108, 118}; // blue: shallow water
    } else if (noise < 0.010f) {
        return {207, 209, 134}; // Beach
    } else {
        if (textureVarNoise < 0.f)
            return {71, 117, 20};
        else if (textureVarNoise < 0.5f)
            return {94, 135, 50};
        else
            return {105, 138, 70};
    }
}

sf::Color TileMap::forest(float noise, float textureVarNoise) {
    std::cout << "forest" << std::endl;
    if (noise < -0.500f) {
        return {2, 43, 68}; // dark blue: deep water
    } else if (noise < -0.10f) {
        return {9, 62, 92}; // deep blue: water
    } else if (noise < -0.060f) {
        return {69, 108, 118}; // blue: shallow water
    } else if (noise < 0.010f) {
        return {207, 209, 134}; // Beach
    } else {
        if (textureVarNoise < 0.f)
            return {71, 117, 20};
        else if (textureVarNoise < 0.5f)
            return {94, 135, 50};
        else
            return {105, 138, 70};
    }
}

sf::Color TileMap::savanne(float noise, float textureVarNoise) {
    std::cout << "savanne" << std::endl;
    if (noise < -0.500f) {
        return {2, 43, 68}; // dark blue: deep water
    } else if (noise < -0.10f) {
        return {9, 62, 92}; // deep blue: water
    } else if (noise < -0.060f) {
        return {69, 108, 118}; // blue: shallow water
    } else if (noise < 0.010f) {
        return {207, 209, 134}; // Beach
    } else {
        if (textureVarNoise < 0.f)
            return {71, 117, 20};
        else if (textureVarNoise < 0.5f)
            return {94, 135, 50};
        else
            return {105, 138, 70};
    }
}

sf::Color TileMap::desert(float noise, float textureVarNoise) {
    std::cout << "dersert" << std::endl;
    if (noise < -0.500f) {
        return {2, 43, 68}; // dark blue: deep water
    } else if (noise < -0.10f) {
        return {9, 62, 92}; // deep blue: water
    } else if (noise < -0.060f) {
        return {69, 108, 118}; // blue: shallow water
    } else if (noise < 0.010f) {
        return {207, 209, 134}; // Beach
    } else {
        if (textureVarNoise < 0.f)
            return {71, 117, 20};
        else if (textureVarNoise < 0.5f)
            return {94, 135, 50};
        else
            return {105, 138, 70};
    }
}

sf::Color TileMap::grasDesert(float noise, float textureVarNoise) {
    std::cout << "gras desert " << std::endl;
    if (noise < -0.500f) {
        return {2, 43, 68}; // dark blue: deep water
    } else if (noise < -0.10f) {
        return {9, 62, 92}; // deep blue: water
    } else if (noise < -0.060f) {
        return {69, 108, 118}; // blue: shallow water
    } else if (noise < 0.010f) {
        return {207, 209, 134}; // Beach
    } else {
        if (textureVarNoise < 0.f)
            return {71, 117, 20};
        else if (textureVarNoise < 0.5f)
            return {94, 135, 50};
        else
            return {105, 138, 70};
    }
}


//TODO: return textures instead
//TODO: create Spritesheet
//TODO: include AnimationComponent
sf::Color TileMap::tileColor(float noise, float textureVariationNoise, float temperature, float humidity) {
    //TODO: Fully implement this.
    if (humidity >= 0.5f) {
        if (temperature > 0.5f) {
            return rainForest(noise, textureVariationNoise);
        } else {
            return swamp(noise, textureVariationNoise);
        }
    } else if (humidity >= 0.f) {
        if (temperature > 0.5f) {
            return saisonalForest(noise, textureVariationNoise);
        } else if (temperature > 0.f) {
            return thickForest(noise, textureVariationNoise);
        } else {
            return taiga(noise, textureVariationNoise);
        }
    } else if (humidity >= -0.5f) {
        if (temperature > 0.5f) {
            return savanne(noise, textureVariationNoise);
        } else if (temperature > 0.f) {
            return forest(noise, textureVariationNoise);
        } else if (temperature > -0.5f) {
            return taiga(noise, textureVariationNoise);
        } else {
            return tundra(noise, textureVariationNoise);
        }
    } else {
        if (temperature > 0.25f) {
            return desert(noise, textureVariationNoise);
        } else if (temperature > -0.5f) {
            return grasDesert(noise, textureVariationNoise);
        } else {
            return tundra(noise, textureVariationNoise);
        }
    }
}

/**
 * Creates a Tile / Object with different parameters given by the player
 * @param pos Position of the Structure / Object
 * @param size Size of the Structure
 * @param color Color of the Structure (Will be replaced by Texture)
 */
void TileMap::createPlayerStructure(sf::Vector2f pos, sf::Vector2f size, sf::Color color) {
    //TODO: Structures will have hitboxes, other than regular tiles
    //TODO: Datastructure for procedural structures (That can be deleted)
    bool blockExists = false;
    for (auto e: structures) {
        if (e->getShape().getPosition() == pos) //When there are multiple blocks it also has to be checked, if it's the same block
            blockExists = true;
    }
    if (!blockExists)
        structures.push_back(new Tile(pos, size, color));

    blockExists = false;
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

    getStructuresInScreenSpace(offset, player_position);

    for (it = tiles.begin(); it != tiles.end();) {
        if ((*it)->getShape().getPosition().x > offset.x + maxTilesX * tileSizeX) { //Rechts vom Monitor
            tileX = (*it)->getShape().getPosition().x - (2 * maxTilesX * tileSizeX);
            tileY = (*it)->getShape().getPosition().y;
            tiles.push_back(new Tile(sf::Vector2f(tileX, tileY), sf::Vector2f(tileSizeX, tileSizeY),
                                     tileColor(
                                             this->geologicalSimplex->fractal(octaves, tileX, tileY) + offsetZ,
                                             this->grasSimplex->fractal(octaves, tileX + 9129834.f, tileY + 1208012.f) + offsetZ,
                                             this->temperature->fractal(octaves, tileX, tileY),
                                             this->humidity->fractal(octaves, tileX, tileY))));
            delete *it;
            it = tiles.erase(it);
        } else if ((*it)->getShape().getPosition().x < offset.x - maxTilesX * tileSizeX) { //Links vom Monitor
            tileX = (*it)->getShape().getPosition().x + (2 * maxTilesX * tileSizeX);
            tileY = (*it)->getShape().getPosition().y;
            tiles.push_back(new Tile(sf::Vector2f(tileX, tileY), sf::Vector2f(tileSizeX, tileSizeY),
                                     tileColor(
                                             this->geologicalSimplex->fractal(octaves, tileX, tileY) + offsetZ,
                                             this->grasSimplex->fractal(octaves, tileX + 9129834.f, tileY + 1208012.f) + offsetZ,
                                             this->temperature->fractal(octaves, tileX, tileY),
                                             this->humidity->fractal(octaves, tileX, tileY))));
            delete *it;
            it = tiles.erase(it);
        }
        if ((*it)->getShape().getPosition().y + tileSizeX > offset.y + maxTilesY * tileSizeY) { //Über dem Monitor
            tileX = (*it)->getShape().getPosition().x;
            tileY = (*it)->getShape().getPosition().y - (2 * maxTilesY * tileSizeY);
            tiles.push_back(new Tile(sf::Vector2f(tileX, tileY), sf::Vector2f(tileSizeX, tileSizeY),
                                     tileColor(
                                             this->geologicalSimplex->fractal(octaves, tileX, tileY) + offsetZ,
                                             this->grasSimplex->fractal(octaves, tileX + 9129834.f, tileY + 1208012.f) + offsetZ,
                                             this->temperature->fractal(octaves, tileX, tileY),
                                             this->humidity->fractal(octaves, tileX, tileY))));
            delete *it;
            it = tiles.erase(it);
        } else if ((*it)->getShape().getPosition().y < offset.y - maxTilesY * tileSizeY) { //Unter dem Monitor
            tileX = (*it)->getShape().getPosition().x;
            tileY = (*it)->getShape().getPosition().y + (2 * maxTilesY * tileSizeY);
            tiles.push_back(new Tile(sf::Vector2f(tileX, tileY), sf::Vector2f(tileSizeX, tileSizeY),
                                     tileColor(
                                             this->geologicalSimplex->fractal(octaves, tileX, tileY) + offsetZ,
                                             this->grasSimplex->fractal(octaves, tileX + 9129834.f, tileY + 1208012.f) + offsetZ,
                                             this->temperature->fractal(octaves, tileX, tileY),
                                             this->humidity->fractal(octaves, tileX, tileY))));
            delete *it;
            it = tiles.erase(it);
        } else {
            ++it;
        }
    }
}

void TileMap::render(sf::RenderTarget &target) {
    for (auto &e: this->tiles) {
        target.draw(e->getShape());
    }
    for (auto &e: this->structuresInScreen) { //TODO: Only if visible
        target.draw(e->getShape());
    }
}