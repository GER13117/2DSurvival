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
Player::Player(float x, float y, sf::Texture *texture) {
    this->initVariables();
    this->initComponents();

    this->createSprite(texture);
    this->setPosition(x, y);
}

Player::~Player() {

}


