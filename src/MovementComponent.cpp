//
// Created by Okke on 22.08.2021.
//

#include "include/MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration)
        : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration) {}

MovementComponent::~MovementComponent() {}

const sf::Vector2f &MovementComponent::getVelocity() const {
    return this->velocity;
}

//functions
const bool MovementComponent::isIdle() const {
    if (this->velocity.x == 0.f && this->velocity.y == 0.f)
        return true;
    return false;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float &dt) {
    this->velocity.x += this->acceleration * dir_x * dt;
    this->velocity.y += this->acceleration * dir_y * dt;
}

void MovementComponent::update(const float &dt) {
    if (this->velocity.x > 0.f) {

        //maxVelocity-check
        if (this->velocity.x > maxVelocity) {
            this->velocity.x = this->maxVelocity;
        }

        //deceleration-check
        this->velocity.x -= deceleration * dt;
        if (this->velocity.x < 0.f) {
            this->velocity.x = 0.f;
        }

    } else if (this->velocity.x < 0.f) {

        //maxVelocity-check
        if (this->velocity.x < -maxVelocity) {
            this->velocity.x = -this->maxVelocity;
        }

        this->velocity.x += deceleration * dt;
        if (this->velocity.x > 0.f) {
            this->velocity.x = 0.f;
        }
    }

    if (this->velocity.y > 0.f) {

        //maxVelocity-check
        if (this->velocity.y > maxVelocity) {
            this->velocity.y = this->maxVelocity;
        }

        //deceleration-check
        this->velocity.y -= deceleration * dt;
        if (this->velocity.y < 0.f) {
            this->velocity.y = 0.f;
        }

    } else if (this->velocity.y < 0.f) {

        //maxVelocity-check
        if (this->velocity.y < -maxVelocity) {
            this->velocity.y = -this->maxVelocity;
        }

        this->velocity.y += deceleration * dt;
        if (this->velocity.y > 0.f) {
            this->velocity.y = 0.f;
        }
    }

    //Final move
    this->sprite.move(this->velocity * dt); //uses velocity
}