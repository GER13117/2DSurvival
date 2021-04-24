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

void MainMenuState::initButtons() {
    this->buttons["GAME_STATE"] = new Button(100.f, 100.f, 150, 50,
                                             &this->commando, 20, "New Game",
                                             sf::Color::Red, sf::Color::Green, sf::Color::Cyan);
    this->buttons["EXIT_STATE"] = new Button(100.f, 300.f, 150, 50,
                                             &this->commando, 20, "Quit",
                                             sf::Color::Red, sf::Color::Green, sf::Color::Cyan);
}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys)
        : State(window, supportedKeys) {
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
    this->background.setSize(static_cast<sf::Vector2f> (window->getSize()));
    this->background.setFillColor(sf::Color::Blue);
}

MainMenuState::~MainMenuState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }
}

void MainMenuState::updateInput(const float &dt) {
    this->checkForQuit();
}

void MainMenuState::updateButtons() {
    for (auto &it : this->buttons) {
        it.second->update(this->mousePosView);
    }
    //New Game
    if (this->buttons["GAME_STATE"]->isPressed()){
        std::cout << "Doesnt work yet snitches" << std::endl << "Will look like: " << std::endl << "this->states.push(new GameState(this->window, &this->supportedKeys))";
        //this->states.push(new GameState(this->window, &this->supportedKeys));
    }

    //Quit Game
    if (this->buttons["EXIT_STATE"]->isPressed()){
        this->quit = true;
    }
}

void MainMenuState::update(const float &dt) {
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget *target) {
    for (auto &it : this->buttons) {
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->window;
    }
    target->draw(this->background);
    this->renderButtons(target);
}

void MainMenuState::endState() {
    std::cout << "Ending MainMenuState" << std::endl;
}