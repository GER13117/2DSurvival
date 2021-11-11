//
// Created by okke on 23.04.21.
//
#include "include/MainMenuState.h"

void MainMenuState::initVariables() {

}

void MainMenuState::initBackground() {
    this->background.setSize(static_cast<sf::Vector2f>(this->window->getSize()));
    if (!this->bgTexture.loadFromFile("../resources/Pictures/Backgrounds/bgplaceholder.png")) {
        throw std::string("ERROR:MAINMENUSTATE::Could not load bgplaceholder.png");
    }
    this->background.setTexture(&this->bgTexture);
}

void MainMenuState::initFonts() {
    if (!this->arial.loadFromFile("../resources/Fonts/arial.ttf")) {
        throw std::string("ERROR::MAINMENUSTATE::COULD NOT LOAD ARIAL FONT");
    }
    if (!this->commando.loadFromFile("../resources/Fonts/commando.ttf")) {
        throw std::string("ERROR::MAINMENUSTATE::COULD NOT LOAD COMMANDO FONT");
    }
}

void MainMenuState::initKeybinds() {
    std::ifstream ifs("../cfg/mainmenustate_keybinds.ini");
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
    this->centerWidth = (static_cast<float>(window->getSize().x)) / 2.f;
    this->centerHeight = (static_cast<float>(window->getSize().y)) / 2.f;
    this->buttons["GAME_STATE"] = new Button(centerWidth, centerHeight - 100, 250, 50,
                                             &this->commando, 20, "New Game",
                                             sf::Color::Red, sf::Color::Green, sf::Color::Cyan);

    this->buttons["SETTINGS"] = new Button(centerWidth, centerHeight + 100, 250, 50,
                                           &this->commando, 20, "Settings",
                                           sf::Color::Red, sf::Color::Green, sf::Color::Cyan);

    this->buttons["EXIT_STATE"] = new Button(centerWidth, centerHeight + 300, 250, 50,
                                             &this->commando, 20, "Quit",
                                             sf::Color::Red, sf::Color::Green, sf::Color::Cyan);
}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                             std::stack<State *> *states)
        : State(window, supportedKeys, states) {
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

MainMenuState::~MainMenuState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }
}

void MainMenuState::updateInput(const float &dt) {
}

void MainMenuState::updateButtons() {
    for (auto &it : this->buttons) {
        it.second->update(this->mousePosView);
    }
    //New Game
    if (this->buttons["GAME_STATE"]->isPressed()) {
        this->states->push(new GameState(this->window, this->supportedKeys, this->states, this->arial));
    }

    //Quit Game
    if (this->buttons["EXIT_STATE"]->isPressed()) {
        this->endState();
    }

    if (this->buttons["SETTINGS"]->isPressed()) {
        std::cout << "In Production" << std::endl;
    }
}

void MainMenuState::update(const float &dt) {
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget &target) {
    for (auto &it : this->buttons) {
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->window;
    }
    target->draw(this->background);
    this->renderButtons(*target);
}