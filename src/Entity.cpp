//
// Created by okke on 22.04.21.
//
#include "include/Entity.h"

void Entity::initVariables() {
    this->texture = nullptr;
    this->sprite = nullptr;
    this->movementSpeed = 100.f;
}

Entity::Entity() {
    this->initVariables();
}

Entity::~Entity() {
    delete this->sprite;
}

//Component functions
void Entity::createSprite(sf::Texture *texture) {
    this->texture = texture;
    this->sprite = new sf::Sprite(*this->texture);
}

//Functions
void Entity::setPosition(const float x, const float y) {
    if (this->sprite) {
        this->sprite->setPosition(x, y);
    }
}

void Entity::move(const float &dt, const float dir_x, const float dir_y) {
    if (this->sprite) {
        this->sprite->move(dir_x * this->movementSpeed * dt, dir_y * this->movementSpeed * dt);
    }
}

void Entity::update(const float &dt) {
}

void Entity::render(sf::RenderTarget *target) {
    if (this->sprite) {
        target->draw(*this->sprite);
    }
}