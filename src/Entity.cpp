//
// Created by okke on 22.04.21.
//
#include "include/Entity.h"

void Entity::initVariables() {
    this->movementComponent = nullptr;
}

Entity::Entity() {
    this->initVariables();
}

Entity::~Entity() {
    delete this->movementComponent;
}

//Component functions
void Entity::setTexture(sf::Texture &texture) {
    this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity,const float acceleration,
                                     const float deceleration) {
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}


//Functions
void Entity::setPosition(const float x, const float y) {

        this->sprite.setPosition(x, y);
}

const sf::Vector2f &Entity::getPosition() const {
    return this->sprite.getPosition();
}

void Entity::move(const float dir_x, const float dir_y, const float &dt) {
    if (this->movementComponent) {
        this->movementComponent->move(dir_x, dir_y, dt); //Set velocity

    }
}

void Entity::update(const float &dt) {
    if (this->movementComponent)
        this->movementComponent->update(dt);
}

void Entity::render(sf::RenderTarget &target) {
        target.draw(this->sprite);
}



