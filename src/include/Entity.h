//
// Created by okke on 22.04.21.
//
#ifndef ENTITY_H
#define ENTITY_H

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "Tile.h"

#include "Collision.h"

class Entity {
private:
    void initVariables();

protected:
    sf::Sprite sprite;
    HitboxComponent *hitboxComponent{};
    MovementComponent *movementComponent{};
    AnimationComponent *animationComponent{};
public:
    Entity();

    virtual ~Entity();

    //Component functions
    void setTexture(sf::Texture &texture);

    void createHitboxComponent(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height);

    void createMovementComponent(const float maxVelocity, const float acceleration,
                                 const float deceleration);

    void createAnimationComponent(sf::Texture &texture_sheet);

    //Functions
    virtual void setPosition(const float x, const float y);

    virtual const sf::Vector2f &getPosition() const;

    virtual void move(const float dir_x, const float dir_y, const float &dt);

    virtual void update(const float &dt, const std::vector<Tile *>& structures) = 0;

    virtual void render(sf::RenderTarget &target, bool show_hitbox) = 0;
};

#endif
