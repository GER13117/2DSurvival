//
// Created by Okke on 27.08.2021.
//
#ifndef INC_2DSURVIVAL_TILE_H
#define INC_2DSURVIVAL_TILE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <iostream>
#include <cmath>

class Tile {
private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture &textureSheet;
    sf::Vector2f pos;
    sf::IntRect textureRect;
public:
    Tile(sf::Vector2f pos, sf::Texture &texture_sheet, sf::IntRect text_rect, float rotation);

    virtual ~Tile();

    //Accessors
    const sf::Vector2f &getPosition();

    sf::FloatRect getGlobalBounds();

    //Functions
    void update();

    void render(sf::RenderTarget &target);
};

#endif //INC_2DSURVIVAL_TILE_H