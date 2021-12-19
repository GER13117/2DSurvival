//
// Created by Okke on 24.08.2021.
//
#include "include/HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite &sprite,
                                 float offset_x, float offset_y,
                                 float width, float height)
        : sprite(sprite),
          offsetX(offset_x), offsetY(offset_y) {
    this->hitBox.setPosition(sf::Vector2f {this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y});
    this->hitBox.setSize(sf::Vector2f(width, height));
    this->hitBox.setFillColor(sf::Color::Transparent);
    //this->hitBox.setOutlineThickness(1.f);
    //this->hitBox.setOutlineColor(sf::Color::Magenta);
}

HitboxComponent::~HitboxComponent() {
}

bool HitboxComponent::checkIntersect(const sf::FloatRect &frect) {
    return this->hitBox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update() {
    this->hitBox.setPosition(sf::Vector2f {this->sprite.getPosition().x + this->offsetX,
                             this->sprite.getPosition().y + this->offsetY});
}

void HitboxComponent::render(sf::RenderTarget &target) {
    target.draw(this->hitBox);
}