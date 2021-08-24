//
// Created by okke on 23.04.21.
//

#include "include/Button.h"

Button::Button(float x, float y, float width, float height,
               sf::Font *font, unsigned int fontSize, const std::string &textString,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) {
    this->buttonState = BTN_IDLE;
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setOrigin(shape.getSize().x / 2.f, shape.getSize().y / 2.f);

    this->shape.setPosition(sf::Vector2f(x, y));

    this->font = font;

    this->text.setFont(*this->font);
    this->text.setString(textString);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(fontSize);
    sf::FloatRect textRect = text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width / 2.f,
                         textRect.top + textRect.height / 2.f);
    this->text.setPosition(
            this->shape.getPosition().x,
            this->shape.getPosition().y
    );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;
    this->shape.setFillColor(this->idleColor);
}

Button::~Button() {

}

//Accessors
bool Button::isPressed() const {
    if (this->buttonState == BTN_ACTIVE) {
        return true;
    } else {
        return false;
    }
}

//Functions
void Button::update(const sf::Vector2f mousePos) {
    /*
     * Updates the booleans for hover and press
     */
    this->buttonState = BTN_IDLE;
    if (this->shape.getGlobalBounds().contains(mousePos)) {
        this->buttonState = BTN_HOVER;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->buttonState = BTN_ACTIVE;
        }
    }
    switch (this->buttonState) {
        case BTN_IDLE:
            this->shape.setFillColor(this->idleColor);
            break;
        case BTN_HOVER:
            this->shape.setFillColor(this->hoverColor);
            break;
        case BTN_ACTIVE:
            this->shape.setFillColor(this->activeColor);
            break;
        default:
            this->shape.setFillColor(sf::Color::Red);
            break;
    }

}

void Button::render(sf::RenderTarget &target) {
    target.draw(this->shape);
    target.draw(this->text);
}