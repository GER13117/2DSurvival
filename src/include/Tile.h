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
    sf::Color tileColor; //TODO: Replace with texture
    sf::Sprite &sprite;
    sf::Texture &textureSheet;
    sf::Vector2f pos;
    sf::IntRect &textureRect;
public:
    Tile(sf::Vector2f pos, sf::Vector2f size,
         sf::Color tileColor);

    Tile(sf::Vector2f pos, sf::Texture &texture_sheet, sf::Sprite &sprite, sf::IntRect &text_rect);

    virtual ~Tile();

    //Accessors
    sf::RectangleShape getShape();

    //Functions
    void update();

    void render(sf::RenderTarget &target);
};

#endif //INC_2DSURVIVAL_TILE_H