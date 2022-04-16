//
// Created by Okke on 20.12.2021.
//

#include "include/PauseMenu.h"

void PauseMenu::initButtons() {
    this->centerWidth = (static_cast<float>(canvasSize.x)) / 2.f;
    this->centerHeight = (static_cast<float>(canvasSize.y)) / 2.f;
}

PauseMenu::PauseMenu(sf::Vector2f pos, sf::Vector2f size) {
    this->canvasPos = pos;
    this->canvasSize = size;
    this->mainShape.setSize(this->canvasSize);
    this->mainShape.setPosition(this->canvasPos);
    this->mainShape.setFillColor({255, 0, 0, 128});
    this->initButtons();
}

PauseMenu::~PauseMenu() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }
}

void PauseMenu::renderButtons(sf::RenderTarget &target) {
    for (auto &it: this->buttons) {
        it.second->render(target);
    }
}


void PauseMenu::update(sf::Vector2f mousePos) {

}

void PauseMenu::render(sf::RenderTarget &target) {
    target.draw(this->mainShape);
}



