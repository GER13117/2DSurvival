//
// Created by Okke on 27.08.2021.
//
#include "include/Tile.h"
Tile::Tile(sf::Vector2f pos, sf::Texture &texture_sheet, sf::IntRect text_rect, float rotation)
        : textureSheet(texture_sheet), textureRect(text_rect) {
    this->sprite.setTexture(textureSheet);
    this->sprite.setTextureRect(textureRect);
    this->sprite.setPosition(pos);
    this->sprite.setOrigin(this->sprite.getLocalBounds().getSize()/2.f);
    this->sprite.setRotation(sf::degrees(rotation));
    sf::Vector2f mirror;
    if ((int) pos.x % 2 == 0)
        mirror.x = 1;
    else
        mirror.x = -1;

    if ((int) pos.y % 2 == 0)
        mirror.y = 1;
    else
        mirror.y = -1;

    this->sprite.setScale(mirror);
}

Tile::~Tile() {
}

const sf::Vector2f &Tile::getPosition() {
    return this->sprite.getPosition();
}

void Tile::update() {
}

void Tile::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
}

sf::FloatRect Tile::getGlobalBounds() {
    return this->sprite.getGlobalBounds();
}
