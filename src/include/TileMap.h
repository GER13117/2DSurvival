//
// Created by Okke on 27.08.2021.
//
#ifndef INC_2DSURVIVAL_TILEMAP_H
#define INC_2DSURVIVAL_TILEMAP_H

#include "Tile.h"
#include "../../libs/noise/SimplexNoise.h"

class TileMap {
private:
    //Vectors, Maps
    std::map<std::string, int> terrainNumbers;
    std::vector<Tile *> tiles;
    std::vector<Tile *> structures; //built by the player
    std::vector<Tile *>::iterator it;

    std::vector<Tile *> structuresInScreen;

    sf::Texture &textureSheet;

    //inits and utilities
    void spawnTile(sf::Vector2f pos);

    void initTerrainNumbers();

    void initNoise();

    void createTileMapStart();

    sf::IntRect getTileRect(const std::string &terrain, float noise, float textureVarNoise);

    sf::IntRect getTileTerrain(float noise, float textureVariationNoise, float fTemperature, float fHumidity);

    //Tile
    sf::Vector2i offset;
    int tileSizeX;
    int tileSizeY;
    uint8_t maxTilesX;
    uint8_t maxTilesY;

    float geologicalScale{};
    float grasScale{};
    float temperatureScale{};
    float humidityScale{};
    float offsetZ{};
    float lacunarity{};
    float persistance{};
    int octaves{};

    void findStructuresInScreenSpace(sf::Vector2i view_offset);

    SimplexNoise *geologicalSimplex{};
    SimplexNoise *grasSimplex{};
    SimplexNoise *temperature{};
    SimplexNoise *humidity{};
    SimplexNoise *tileRotation{};

public:
    TileMap(sf::Texture &map_texture_sheet, int tile_size_x, int tile_size_y, sf::Vector2f player_position, uint8_t max_tiles_x,
            uint8_t max_tiles_y);

    void createPlayerStructure(sf::Vector2f pos, sf::Vector2i size);

    void update(sf::Vector2f player_position);

    void render(sf::RenderTarget &target);

    std::vector<Tile *> getStructuresInScreen();

    virtual ~TileMap();
};

#endif //INC_2DSURVIVAL_TILEMAP_H