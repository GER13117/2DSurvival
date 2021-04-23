//
// Created by okke on 23.04.21.
//

#include "MainMenuState.h"

void MainMenuState::initKeybinds() {

    std::ifstream ifs("../cfg/gamestate_keybinds.ini");

    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();
/*
    //Degug REMOVE
    for (auto i: this->keybinds) {
        std::cout << i.first << " " << i.second << std::endl;
    }*/
}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys)
        : State(window, supportedKeys) {
    this->initKeybinds();
    this->background.setSize(static_cast<sf::Vector2f> (window->getSize()));
    this->background.setFillColor(sf::Color::Blue);
}

MainMenuState::~MainMenuState() {
}

void MainMenuState::updateInput(const float &dt) {
    this->checkForQuit();


}

void MainMenuState::update(const float &dt) {
    this->updateInput(dt);
}

void MainMenuState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->window;
        target->draw(this->background);
    }
}

void MainMenuState::endState() {
    std::cout << "Ending MainMenuState" << std::endl;
}