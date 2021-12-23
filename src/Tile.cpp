//
// Created by Okke on 27.08.2021.
//
#include "include/Tile.h"

Tile::Tile(sf::Vector2f pos, sf::Vector2f size, sf::Color tileColor) {
    this->tileColor = tileColor;
    this->shape.setSize(size);
    this->shape.setPosition(pos);
    this->shape.setFillColor(this->tileColor);
//    this->shape.setOutlineThickness(2.f);
//    this->shape.setOutlineColor(sf::Color::Black);
}

Tile::~Tile() {
}

sf::RectangleShape Tile::getShape() {
    return this->shape;
}

void Tile::update() {
}