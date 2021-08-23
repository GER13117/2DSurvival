#ifndef INC_2DSURVIVAL_MOVEMENTCOMPONENT_H
#define INC_2DSURVIVAL_MOVEMENTCOMPONENT_H

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

enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent {
private:
    sf::Sprite &sprite;

    float acceleration;
    float deceleration;
    float maxVelocity{};

    sf::Vector2f velocity;

    //Initializers

public:
    MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration);

    virtual ~MovementComponent();

    //accessors
    const sf::Vector2f &getVelocity() const;

    //functions
    const bool getState(const short unsigned state) const;
    void move(const float dir_x, const float dir_y, const float &dt);

    void update(const float &dt);
};

#endif //INC_2DSURVIVAL_MOVEMENTCOMPONENT_H