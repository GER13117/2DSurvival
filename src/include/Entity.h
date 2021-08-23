//
// Created by okke on 22.04.21.
//
#include "MovementComponent.h"
#include "AnimationComponent.h"

#ifndef ENTITY_H
#define ENTITY_H

class Entity {
private:
    void initVariables();

protected:
    sf::Sprite sprite;
    MovementComponent *movementComponent;
    AnimationComponent *animationComponent;
public:
    Entity();

    virtual ~Entity();

    //Component functions
    void setTexture(sf::Texture &texture);

    void createMovementComponent(const float maxVelocity, const float acceleration,
                                 const float deceleration);
    void createAnimationComponent(sf::Texture &texture_sheet);


    //Functions
    virtual void setPosition(const float x, const float y);

    virtual const sf::Vector2f &getPosition() const;

    virtual void move(const float dir_x, const float dir_y, const float &dt);

    virtual void update(const float &dt);

    virtual void render(sf::RenderTarget &target);

};

#endif
