//
// Created by okke on 22.04.21.
//
#include "State.h"

State::State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys) {
    this->window = window;
    this->supportedKeys = supportedKeys;
    this->quit = false;
}

State::~State() {
}

void State::checkForQuit() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
        this->quit = true;
    }
}

const bool &State::getQuit() const {
    return this->quit;
}
