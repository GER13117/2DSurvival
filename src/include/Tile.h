//
// Created by Okke on 27.08.2021.
//

#ifndef INC_2DSURVIVAL_TILE_H
#define INC_2DSURVIVAL_TILE_H

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

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
    short unsigned buttonState;

    sf::RectangleShape shape;

    sf::Color tileColor; //TODO: Replace with texture

public:
    Tile(float x, float y, float width, float height,
         sf::Color tileColor);

    virtual ~Tile();

    //Accessors
    sf::RectangleShape getShape();

    //Functions
    void update();
};


#endif //INC_2DSURVIVAL_TILE_H