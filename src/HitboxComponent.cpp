//
// Created by Okke on 24.08.2021.
//
#include "include/HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite &sprite,
                                 float offset_x, float offset_y,
                                 float width, float height)
        : sprite(sprite),
          offsetX(offset_x), offsetY(offset_y) {
    this->hitBox.setPosition(sf::Vector2f{this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y});
    this->hitBox.setSize(sf::Vector2f(width, height));
    this->hitBox.setFillColor(sf::Color::Transparent);
    this->hitBox.setOutlineThickness(1.f);
    this->hitBox.setOutlineColor(sf::Color::Magenta);

    this->nextPosition = {{hitBox.getPosition()},
                          {width, height}};
}

HitboxComponent::~HitboxComponent() {
}

//TODO: Wie kann man an einer Wand entlang laufen, dafür müsste man herausfinden welche seite den Block berührt und einen entsprechenden Rückgabewert haben
bool HitboxComponent::checkStructureIntersect(const std::vector<Tile *> &structures, const sf::Vector2f &velocity, const sf::Vector2f &dir, const float &dt) {
    bool intersects = false;
    if (velocity.x == 0.f)
        this->nextPosition.left = this->hitBox.getPosition().x + dir.x;
    else
        this->nextPosition.left = this->hitBox.getPosition().x + velocity.x * dt;

    if (velocity.y == 0.f)
        this->nextPosition.top = this->hitBox.getPosition().y + dir.y;
    else
        this->nextPosition.top = this->hitBox.getPosition().y + velocity.y * dt;

    for (auto i: structures) {
        if (std::nullopt == this->nextPosition.findIntersection(i->getGlobalBounds())) {
            this->hitBox.setOutlineColor(sf::Color::Green);
        } else {
            this->hitBox.setOutlineColor(sf::Color::Red);
            intersects = true;
        }
    }
    return intersects;
}

void HitboxComponent::update() {
    this->hitBox.setPosition(sf::Vector2f{this->sprite.getPosition().x + this->offsetX,
                                          this->sprite.getPosition().y + this->offsetY});
}

void HitboxComponent::render(sf::RenderTarget &target) {
    target.draw(this->hitBox);
}