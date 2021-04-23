//
// Created by okke on 23.04.21.
//
#include "MainMenuState.h"

void MainMenuState::initFonts() {
    if (!this->arial.loadFromFile("../Fonts/arial.ttf")) {
        throw ("ERROR::MAINMENUSTATE::COULD NOT LOAD ARIAL FONT");
    }
    if (!this->commando.loadFromFile("../Fonts/commando.ttf")) {
        throw ("ERROR::MAINMENUSTATE::COULD NOT LOAD COMMANDO FONT");
    }
}

void MainMenuState::initKeybinds() {
    std::ifstream ifs("../cfg/gamestate_keybinds.ini");
    if (ifs.is_open()) {
        std::string key;
        std::string key2;
        while (ifs >> key >> key2) {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys)
        : State(window, supportedKeys) {
    this->initFonts();
    this->initKeybinds();
    //Test
    this->gamestate_btn = new Button(100.f, 100.f, 150, 50,
                                     &this->commando, 20, "New Game",
                                     sf::Color::Red, sf::Color::Green, sf::Color::Cyan);
    this->background.setSize(static_cast<sf::Vector2f> (window->getSize()));
    this->background.setFillColor(sf::Color::Blue);
}

MainMenuState::~MainMenuState() {
    delete this->gamestate_btn;
}

void MainMenuState::updateInput(const float &dt) {
    this->checkForQuit();
}

void MainMenuState::update(const float &dt) {
    this->updateMousePositions();
    this->updateInput(dt);
    this->gamestate_btn->update(this->mousePosView);
}

void MainMenuState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->window;
    }
    target->draw(this->background);
    this->gamestate_btn->render(target);
}

void MainMenuState::endState() {
    std::cout << "Ending MainMenuState" << std::endl;
}
