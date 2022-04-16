#ifndef INC_2DSURVIVAL_MOVEMENTCOMPONENT_H
#define INC_2DSURVIVAL_MOVEMENTCOMPONENT_H

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

enum movement_states {
    IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN
};

class MovementComponent {
private:
    sf::Sprite &sprite;
    float acceleration;
    float deceleration;
    float maxVelocity{};
    sf::Vector2f velocity;
    sf::Vector2f inputDir;
    float diagonalMaxV;
    static float Q_rsqrt(float number);
    //Initializers
public:
    MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration);

    virtual ~MovementComponent();

    //accessors
    [[nodiscard]] const sf::Vector2f &getVelocity() const;

    [[nodiscard]] const sf::Vector2f &getInputDir() const;

    //functions
    [[nodiscard]] bool getState(short unsigned state) const;

    void move(float dir_x, float dir_y, const float &dt);

    void update(const float &dt, bool collision);
};

#endif //INC_2DSURVIVAL_MOVEMENTCOMPONENT_H