//
// Created by Okke on 27.08.2021.
//
#include "include/TileMap.h"


//TODO: replace all functions returning sf::Color return a sf::IntRect instead
//TODO: create Spritesheet
//TODO: include AnimationComponent (MAYBE for water)

void TileMap::initTerrainNumbers() {
    this->terrainNumbers["RAINFOREST"] = 0;
    this->terrainNumbers["TUNDRA"] = 1;
    this->terrainNumbers["SWAMP"] = 2;
    this->terrainNumbers["TAIGA"] = 3;
    this->terrainNumbers["SEASONAL_FOREST"] = 4;
    this->terrainNumbers["FOREST"] = 5;
    this->terrainNumbers["WOODS"] = 6;
    this->terrainNumbers["SAVANNE"] = 7;
    this->terrainNumbers["DESERT"] = 8;
    this->terrainNumbers["GRAS_DESERT"] = 9;
}

void TileMap::initNoise() {
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
    this->tileRotation = new SimplexNoise(0.1f / 0.0001f, 0.1f, lacunarity, persistance);

    this->octaves = static_cast<int>(3 + std::log(geologicalScale)); // Estimate number of octaves needed for the scale
}

void TileMap::createTileMapStart() {
    /**
     * This loop draws tiles on the whole screen when the Tilemap is created. In "update" tiles get appended or removed.
     */
    for (int x = offset.x - maxTilesX * tileSizeX; x < maxTilesX * tileSizeX + offset.x; x += tileSizeX) {
        for (int y = offset.y - maxTilesY * tileSizeY; y < maxTilesY * tileSizeY + offset.y; y += tileSizeY) {
            spawnTile({(float) x, (float) y});
        }
    }
}

TileMap::TileMap(sf::Texture &map_texture_sheet, int tile_size_x, int tile_size_y, sf::Vector2f player_position, uint8_t max_tiles_x, uint8_t max_tiles_y)
        : textureSheet(map_texture_sheet),
          tileSizeX(tile_size_x), tileSizeY(tile_size_y),
          offset(static_cast<sf::Vector2i>(player_position)),
          maxTilesX(max_tiles_x), maxTilesY(max_tiles_y) {

    this->initTerrainNumbers();
    this->initNoise();
    this->createTileMapStart();
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
    delete geologicalSimplex;
    delete grasSimplex;
    delete temperature;
    delete humidity;

}

void TileMap::getStructuresInScreenSpace(sf::Vector2i view_offset) {
    structuresInScreen.clear();
    for (auto i: structures) {
        if (i->getPosition().x > view_offset.x + maxTilesX * tileSizeX || i->getPosition().x < view_offset.x - maxTilesX * tileSizeX ||
            i->getPosition().y > view_offset.y + maxTilesX * tileSizeX || i->getPosition().y < view_offset.y - maxTilesX * tileSizeX)
            continue;
        else
            structuresInScreen.push_back(i);
    }
}

/*
 * Terrain numbering scheme
 * 0 = rain forest
 * 1 = tundra
 * 2 = swamp
 * 3 = taiga
 * 4 = seasonal woods
 * 5 = forest
 * 6 = woods
 * 7 = savanne
 * 8 = desert
 * 9 = gras desert
 */

//TODO: CHANGE THESE NUMBERS ACCORDINGLY
sf::IntRect TileMap::getTileRect(const std::string &terrain, float noise, float textureVarNoise) {
    int tileType;
    if (noise < -0.500f) {
        tileType = 16; // dark blue: deep water //TODO: Add tile to sprite sheet
    } else if (noise < -0.20f) {
        tileType = 15; // deep blue: water
    } else if (noise < -0.10f) {
        tileType = 14; // blue: shallow water
    } else if (noise < 0.035f) {
        tileType = 13; // Beach
    } else if (noise < 0.8f) {
        if (textureVarNoise < -0.2f)
            tileType = 0;
        else if (textureVarNoise < -0.1f)
            tileType = 1;
        else if (textureVarNoise < 0.0f)
            tileType = 2;
        else if (textureVarNoise < 0.1f)
            tileType = 3;
        else if (textureVarNoise < 0.2f)
            tileType = 4;
        else if (textureVarNoise < 0.3f)
            tileType = 5;
        else if (textureVarNoise < 0.4f)
            tileType = 6;
        else if (textureVarNoise < 0.5f)
            tileType = 7;
        else if (textureVarNoise < 0.6f)
            tileType = 8;
        else if (textureVarNoise < 0.7f)
            tileType = 9;
        else if (textureVarNoise < 0.8f)
            tileType = 10;
        else if (textureVarNoise < 0.9f)
            tileType = 11;
        else
            tileType = 12;
    } else {
        if (textureVarNoise < 0.f)
            tileType = 15;
        else
            tileType = 15;
    }
    return {{tileType * tileSizeX, terrainNumbers[terrain] * tileSizeY},
            {tileSizeX,            tileSizeY}};
}

sf::IntRect TileMap::getTileTerrain(float noise, float textureVariationNoise, float fTemperature, float fHumidity) {
    if (fHumidity >= 0.5f) {
        if (fTemperature > 0.5f) {
            return getTileRect("RAINFOREST", noise, textureVariationNoise);
        } else {
            return getTileRect("SWAMP", noise, textureVariationNoise);
        }
    } else if (fHumidity >= 0.f) {
        if (fTemperature > 0.5f) {
            return getTileRect("SEASONAL_FOREST", noise, textureVariationNoise);
        } else if (fTemperature > 0.f) {
            return getTileRect("FOREST", noise, textureVariationNoise);
        } else {
            return getTileRect("TAIGA", noise, textureVariationNoise);
        }
    } else if (fHumidity >= -0.5f) {
        if (fTemperature > 0.5f) {
            return getTileRect("SAVANNE", noise, textureVariationNoise);
        } else if (fTemperature > 0.f) {
            return getTileRect("WOODS", noise, textureVariationNoise);
        } else if (fTemperature > -0.5f) {
            return getTileRect("TAIGA", noise, textureVariationNoise);
        } else {
            return getTileRect("TUNDRA", noise, textureVariationNoise);
        }
    } else {
        if (fTemperature > 0.25f) {
            return getTileRect("DESERT", noise, textureVariationNoise);
        } else if (fTemperature > -0.5f) {
            return getTileRect("GRAS_DESERT", noise, textureVariationNoise);
        } else {
            return getTileRect("TUNDRA", noise, textureVariationNoise);
        }
    }
}

/**
 * Creates a Tile / Object with different parameters given by the player
 * @param pos Position of the Structure / Object
 * @param size Size of the Structure
 * @param color Color of the Structure (Will be replaced by Texture)
 */
void TileMap::createPlayerStructure(sf::Vector2f pos, sf::Vector2i size) {
    //TODO: Structures will have hitboxes, other than regular tiles
    //TODO: Datastructure for procedural structures (That can be deleted)
    bool blockExists = false;
    for (auto e: structures) {
        if (e->getPosition() == pos) //When there are multiple blocks it also has to be checked, if it's the same block
            blockExists = true;
    }
    if (!blockExists)
        structures.push_back(new Tile(pos, this->textureSheet, {{0, 0}, size}, 0.f));
}

/**
 * function containing all functionality to create a new procedural tile. Generatings things like seeds also get a lot easier
 * @param pos of the tile
 */
void TileMap::spawnTile(sf::Vector2f pos) {
    tiles.push_back(new Tile(pos, this->textureSheet,
                             getTileTerrain(
                                     this->geologicalSimplex->fractal(octaves, pos.x, pos.y) + offsetZ,
                                     this->grasSimplex->fractal(octaves, pos.x + 9129834.f, pos.y + 1208012.f) +
                                     offsetZ, //arbitrary number to  offset the continent-noise and tex-variation, as they are the same just on a different scale
                                     this->temperature->fractal(octaves, pos.x, pos.y),
                                     this->humidity->fractal(octaves, pos.x, pos.y)),
                             (float) ((int) (((this->tileRotation->fractal(octaves, pos.x, pos.y) + 1) * 270) / 90)) * 90.f));
}

//TODO: maybe only update the map if the player is moving?
/**
 * removes and appends tiles from the tiles vector by checking if its position is within the screen.
 * @param player_position is used to calculate the offset from 0,0 rounded by the size of a tile.
 */
void TileMap::update(sf::Vector2f player_position) {
    offset.x = ((int) (player_position.x / (float) tileSizeX) * tileSizeX);
    offset.y = ((int) (player_position.y / (float) tileSizeY) * tileSizeY);

    getStructuresInScreenSpace(offset);

    for (it = tiles.begin(); it != tiles.end();) {
        if ((*it)->getPosition().x > offset.x + maxTilesX * tileSizeX) { //Rechts vom Monitor
            spawnTile({(*it)->getPosition().x - (2 * maxTilesX * tileSizeX), (*it)->getPosition().y});
            delete *it;
            it = tiles.erase(it);
        } else if ((*it)->getPosition().x < offset.x - maxTilesX * tileSizeX) { //Links vom Monitor
            spawnTile({(*it)->getPosition().x + (2 * maxTilesX * tileSizeX), (*it)->getPosition().y});
            delete *it;
            it = tiles.erase(it);
        }
        if ((*it)->getPosition().y + tileSizeX > offset.y + maxTilesY * tileSizeY) { //Über dem Monitor
            spawnTile({(*it)->getPosition().x, (*it)->getPosition().y - (2 * maxTilesY * tileSizeY)});
            delete *it;
            it = tiles.erase(it);
        } else if ((*it)->getPosition().y < offset.y - maxTilesY * tileSizeY) { //Unter dem Monitor
            spawnTile({(*it)->getPosition().x, (*it)->getPosition().y + (2 * maxTilesY * tileSizeY)});
            delete *it;
            it = tiles.erase(it);
        } else {
            ++it;
        }
    }
}

void TileMap::render(sf::RenderTarget &target) {
    for (auto &e: this->tiles) {
        e->render(target);
    }
    for (auto &e: this->structuresInScreen) {
        e->render(target);
    }
}