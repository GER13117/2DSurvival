//
// Created by okke on 23.04.21.
//
#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

#include <sstream>
#include <ctime>
#include <cstdlib>
#include <iostream>

enum button_state {
    BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE
};

class Button {
private:
    short unsigned buttonState;

    sf::RectangleShape shape;
    sf::Font *font;
    sf::Text text;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

public:
    Button(float x, float y, float width, float height,
           sf::Font *font, unsigned int fontSize, const std::string& text,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

    virtual ~Button();

    //Accessors
    bool isPressed() const;

    //Functions
    void update(sf::Vector2f mousePos);

    void render(sf::RenderTarget *target);

};

#endif
