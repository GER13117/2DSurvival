//
// Created by okke on 22.04.21.
//
#include "include/Entity.h"

void Entity::initVariables() {
    this->hitboxComponent = nullptr;
    this->movementComponent = nullptr;
    this->animationComponent = nullptr;
}

Entity::Entity() {
    this->initVariables();
}

Entity::~Entity() {
    delete this->hitboxComponent;
    delete this->movementComponent;
    delete this->animationComponent;
}

//Component functions
void Entity::setTexture(sf::Texture &texture) {
    this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height) {
    this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration,
                                     const float deceleration) {
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &texture_sheet) {
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

//Functions
void Entity::setPosition(const float x, const float y) {
    this->sprite.setPosition(sf::Vector2f{x, y});
}

const sf::Vector2f &Entity::getPosition() const {
    return this->sprite.getPosition();
}

void Entity::move(const float dir_x, const float dir_y, const float &dt) { //TODO: Fix Bug that you cant walk anymore
    if (this->movementComponent) {
        this->movementComponent->move(dir_x, dir_y, dt); //Set velocity
    }
}