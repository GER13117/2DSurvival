//
// Created by Okke on 24.08.2021.
//
#ifndef INC_2DSURVIVAL_HITBOXCOMPONENT_H
#define INC_2DSURVIVAL_HITBOXCOMPONENT_H

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include <ctime>
#include <cstdlib>
#include <iostream>

class HitboxComponent {
private:
    sf::Sprite &sprite;
    sf::RectangleShape hitBox;
    float offsetX;
    float offsetY;
public:
    HitboxComponent(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height);

    virtual ~HitboxComponent();

    //functions
    bool checkIntersect(const sf::FloatRect &frect);

    void update();

    void render(sf::RenderTarget &target);
};

#endif //INC_2DSURVIVAL_HITBOXCOMPONENT_H
