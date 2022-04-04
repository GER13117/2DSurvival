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
    static sf::Color tundra(float noise, float textureVarNoise);
    static sf::Color rainForest(float noise, float textureVarNoise);
    static sf::Color swamp(float noise, float textureVarNoise);
    static sf::Color taiga(float noise, float textureVarNoise);
    static sf::Color saisonalForest(float noise, float textureVarNoise);
    static sf::Color thickForest(float noise, float textureVarNoise);
    static sf::Color forest(float noise, float textureVarNoise);
    static sf::Color savanne(float noise, float textureVarNoise);

    static sf::Color desert(float noise, float textureVarNoise);
    static sf::Color grasDesert(float noise, float textureVarNoise);

    std::vector<Tile *> tiles;
    std::vector<Tile *> structures; //built by the player
    std::vector<Tile*>::iterator it;
    sf::Vector2f tileSize;
    sf::Texture textureSheet;
    Tile *tile{};
    sf::Vector2i offset;
    int tileSizeX;
    int tileSizeY;
    float geologicalScale;
    float grasScale;
    float temperatureScale;
    float humidityScale;
    float offsetZ;
    float lacunarity;
    float persistance;
    SimplexNoise *geologicalSimplex;
    SimplexNoise *grasSimplex;
    SimplexNoise *temperature;
    SimplexNoise *humidity;
    int octaves;
    uint8_t maxTilesX;
    uint8_t maxTilesY;
    float tileX;
    float tileY;
public:
    TileMap(int tile_size_x, int tile_size_y, sf::Vector2f player_position, uint8_t max_tiles_x, uint8_t max_tiles_y);

    static sf::Color tileColor(float noise, float textureVariationNoise, float temperature, float humidity);

    void createPlayerStructure(sf::Vector2f pos, sf::Vector2f size, sf::Color color);

    void update(sf::Vector2f player_position);

    void render(sf::RenderTarget &target);

    virtual ~TileMap();
};

#endif //INC_2DSURVIVAL_TILEMAP_H