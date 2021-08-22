//
// Created by okke on 28.04.21.
//

#include "include/Player.h"

//Initializers
void Player::initVariables() {

}

void Player::initComponents() {
    this->createMovementComponent(200.f, 1200.f, 480.f);
}

//Constructor / Destructor
Player::Player(float x, float y, sf::Texture &texture) {
    this->initVariables();
    this->initComponents();

    this->setTexture(texture);
    this->setPosition(x, y);
}

Player::~Player() {

}


