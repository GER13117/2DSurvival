//
// Created by Okke on 22.08.2021.
//
#include "include/MovementComponent.h"

float MovementComponent::Q_rsqrt(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long *) &y;                           // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1);                  // what the fuck?
    y = *(float *) &i;
    y = y * (threehalfs - (x2 * y * y));        // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

    return y;
}

MovementComponent::MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration)
        : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration) {
    diagonalMaxV = maxVelocity * Q_rsqrt(2.f);
}

MovementComponent::~MovementComponent() {}

const sf::Vector2f &MovementComponent::getVelocity() const {
    return this->velocity;
}

const sf::Vector2f &MovementComponent::getInputDir() const {
    return this->inputDir;
}

//functions
bool MovementComponent::getState(const short unsigned state) const {
    switch (state) {
        case IDLE:
            if (this->velocity.x == 0.f && this->velocity.y == 0.f)
                return true;
            break;
        case MOVING:
            if (this->velocity.x != 0.f || this->velocity.y != 0.f)
                return true;
            break;
        case MOVING_LEFT:
            if (this->velocity.x < 0.f)
                return true;
            break;
        case MOVING_RIGHT:
            if (this->velocity.x > 0.f)
                return true;
            break;
        case MOVING_UP:
            if (this->velocity.y < 0.f)
                return true;
            break;
        case MOVING_DOWN:
            if (this->velocity.y > 0.f)
                return true;
            break;
        default:
            if (this->velocity.x == 0.f && this->velocity.y == 0.f)
                return true;
            break;
    }
    return false;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float &dt) {
    this->inputDir = {dir_x, dir_y};
    this->velocity.x += this->acceleration * dir_x * dt;
    this->velocity.y += this->acceleration * dir_y * dt;
}

void MovementComponent::update(const float &dt, const bool collision) {
    if (collision)
        this->velocity = {0, 0};

    if (this->velocity.x != 0.f && this->velocity.y != 0.f) {
        if (this->velocity.x > 0.f) {
            //maxVelocity-check
            if (this->velocity.x > this->diagonalMaxV) {
                this->velocity.x = this->diagonalMaxV;
            }
            //deceleration-check
            this->velocity.x -= deceleration * dt;
            if (this->velocity.x < 0.f) {
                this->velocity.x = 0.f;
            }
        } else if (this->velocity.x < 0.f) {
            //maxVelocity-check
            if (this->velocity.x < -this->diagonalMaxV) {
                this->velocity.x = -this->diagonalMaxV;
            }
            this->velocity.x += deceleration * dt;
            if (this->velocity.x > 0.f) {
                this->velocity.x = 0.f;
            }
        }
        if (this->velocity.y > 0.f) {
            //maxVelocity-check
            if (this->velocity.y > this->diagonalMaxV) {
                this->velocity.y = this->diagonalMaxV;
            }
            //deceleration-check
            this->velocity.y -= deceleration * dt;
            if (this->velocity.y < 0.f) {
                this->velocity.y = 0.f;
            }
        } else if (this->velocity.y < 0.f) {
            //maxVelocity-check
            if (this->velocity.y < -this->diagonalMaxV) {
                this->velocity.y = -this->diagonalMaxV;
            }
            this->velocity.y += deceleration * dt;
            if (this->velocity.y > 0.f) {
                this->velocity.y = 0.f;
            }
        }
    } else {
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
    }
    //Final move
    this->sprite.move(this->velocity * dt); //uses velocity
}