//
// Created by okke on 22.04.21.
//
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <iostream>

#ifndef ENTITY_H
#define ENTITY_H

class Entity {
private:
protected:
    sf::RectangleShape shape;
    float movementSpeed;
public:
    Entity();

    virtual ~Entity();

    //Functions
    virtual void move(const float &dt, const float x, const float y);

    virtual void update(const float &dt);

    virtual void render(sf::RenderTarget *target);

};

#endif
