//
// Created by okke on 22.04.21.
//
#include "Game.h"

//Static Functions
//Initializers
void Game::initWindow() {
    std::ifstream ifs("../cfg/window.ini");
    sf::VideoMode window_bounds(800, 600);
    std::string title = "NONE";
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
    }
    ifs.close();
    this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys() {

    std::ifstream ifs("../cfg/supported_keys.ini");

    if (ifs.is_open()) {
        std::string key = "";
        int key_value;
        while (ifs >> key >> key_value) {
            this->supportedKeys[key] = key_value;
        }
    }
    ifs.close();
/*
    //Degug REMOVE
    for (auto i: this->supportedKeys) {
        std::cout << i.first << " " << i.second << std::endl;
    }*/
}

void Game::initStates() {
    this->states.push(new MainMenuState(this->window, &this->supportedKeys));
}

//Constructor/Destructor
Game::Game() {
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game() {
    delete this->window;
    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

//Functions
void Game::endApplication() {
    std::cout << "ending application" << std::endl;
}

void Game::updateDt() {
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents() {
    while (this->window->pollEvent(this->sfEvent)) {
        if (this->sfEvent.type == sf::Event::Closed) {
            this->window->close();
        }
    }
}

void Game::update() {
    this->updateSFMLEvents();
    if (!this->states.empty()) {
        this->states.top()->update(this->dt);
        if (this->states.top()->getQuit()) {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
        //Ending Application
    else {
        this->endApplication();
        this->window->close();
    }

}

void Game::render() {
    this->window->clear();
    //Render Items
    if (!this->states.empty()) {
        this->states.top()->render();
    }
    this->window->display();
}

void Game::run() {
    while (this->window->isOpen()) {
        this->updateDt();
        this->update();
        this->render();
    }
}