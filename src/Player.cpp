//
// Created by okke on 28.04.21.
//

#include "include/Player.h"

//Initializers
void Player::initVariables() {

}

void Player::initComponents() {

}

//Constructor / Destructor
Player::Player(float x, float y, sf::Texture &texture_sheet) {
    this->initVariables();

    this->setPosition(x, y);

    this->createMovementComponent(200.f, 1700.f, 600.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("WALK_FRONT", 15.f, 0, 0, 3, 0, 32, 49); //Test animation
    this->animationComponent->addAnimation("WALK_LEFT", 15.f, 0, 1, 3, 1, 32, 49); //Test animation
    this->animationComponent->addAnimation("WALK_RIGHT", 15.f, 0, 2, 3, 2, 32, 48); //Test animation
    this->animationComponent->addAnimation("WALK_BACK", 15.f, 0, 3, 3, 3, 32, 48); //Test animation
}

Player::~Player() {

}

void Player::update(const float &dt) {
    this->movementComponent->update(dt);
    this->animationComponent->play("WALK_BACK", dt);
}


