//
// Created by Okke on 27.08.2021.
//
#include "include/Tile.h"
/*
Tile::Tile(sf::Vector2f pos, sf::Vector2f size, sf::Color tileColor) {
    this->tileColor = tileColor;
    this->shape.setSize(size);
    this->shape.setPosition(pos);
    this->shape.setFillColor(this->tileColor);
//    this->shape.setOutlineThickness(2.f);
//    this->shape.setOutlineColor(sf::Color::Black);
}*/

Tile::Tile(sf::Vector2f pos, sf::Texture &texture_sheet, sf::Sprite &sprite, sf::IntRect text_rect)
        : textureSheet(texture_sheet), textureRect(text_rect) {
    this->sprite.setTexture(textureSheet);
    this->sprite.setTextureRect(textureRect);
    this->sprite.setPosition(pos);
}

Tile::~Tile() {
}
/*
sf::RectangleShape Tile::getShape() {
    return this->shape;
}*/

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
