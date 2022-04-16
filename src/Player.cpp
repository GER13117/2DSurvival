//
// Created by okke on 28.04.21.
//

#include "include/Player.h"

//Initializers
void Player::initVariables() {

}

void Player::initComponents() {
}


/**
 * Constructor of the player
 * @param x starting x-position
 * @param y starting y-position
 * @param texture_sheet spritesheet used for the player
 */
Player::Player(float x, float y, int width, int height, sf::Texture &texture_sheet) {
    this->initVariables();

    this->setPosition(x, y);

    this->createHitboxComponent(this->sprite, 0.f, 0.f, width, height);
    this->createMovementComponent(200.f, 1700.f, 600.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 0, 3, 0, width, height); //Test animation
    this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 1, 3, 1, width, height); //Test animation
    this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 0, 2, 3, 2, width, height); //Test animation
    this->animationComponent->addAnimation("WALK_UP", 10.f, 0, 3, 3, 3, width, height); //Test animation
    this->animationComponent->addAnimation("IDLE_FRONT", 10.f, 0, 0, 0, 0, width, height); //Test animation
}

Player::~Player() {}

/**
 * updates the shown texture and position of the player
 * @param dt delta time
 * @param structures in screen
 */
void Player::update(const float &dt, const std::vector<Tile *> &structures) {
    this->movementComponent->update(dt, this->hitboxComponent->checkStructureIntersect(structures, this->movementComponent->getVelocity(), this->movementComponent->getInputDir(), dt));
    if (this->movementComponent->getState(movement_states::MOVING_UP)) {
        this->animationComponent->play("WALK_UP", dt);
    } else if (this->movementComponent->getState(movement_states::MOVING_DOWN)) {
        this->animationComponent->play("WALK_DOWN", dt);
    } else if (this->movementComponent->getState(movement_states::MOVING_LEFT)) {
        this->animationComponent->play("WALK_LEFT", dt);
    } else if (this->movementComponent->getState(movement_states::MOVING_RIGHT)) {
        this->animationComponent->play("WALK_RIGHT", dt);
    } else if (this->movementComponent->getState(movement_states::IDLE)) {
        this->animationComponent->play("IDLE_FRONT", dt);
    }
    this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget &target, const bool show_hitbox) {
    target.draw(this->sprite);

    if (this->hitboxComponent && show_hitbox)
        this->hitboxComponent->render(target);
}
