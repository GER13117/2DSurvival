//
// Created by Okke on 27.08.2021.
//
#include "include/Tile.h"

Tile::Tile(float x, float y, float width, float height, sf::Color tileColor) {
    this->tileColor = tileColor;
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setPosition(sf::Vector2f(x, y));
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