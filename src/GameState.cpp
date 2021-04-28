//
// Created by okke on 22.04.21.
//
#include "include/GameState.h"
void GameState::initKeybinds() {

    std::ifstream ifs("../cfg/gamestate_keybinds.ini");

    if (ifs.is_open()) {
        std::string key;
        std::string key2;
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

void GameState::initTextures() {
    if (!this->textures["PLAYER_IDLE"].loadFromFile("../res/Pictures/Entities/Player/test.png"))
        throw std::string("ERROR::GAMESTATE::INITTEXTURES::COULD NOT LOAD TEST.PNG");
}

void GameState::initPLayers() {
    this->player = new Player(0,0, &this->textures["PLAYER_IDLE"]);
}


GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*> *states)
        : State(window, supportedKeys, states) {
    this->initKeybinds();
    this->initTextures();
    this->initPLayers();
}

GameState::~GameState() {
    delete this->player;
}

void GameState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
        this->player->move(dt, -1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
        this->player->move(dt, 1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
        this->player->move(dt, 0.f, 1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
        this->player->move(dt, 0.f, -1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
        this->endState();
    }
}

void GameState::update(const float &dt) {
    this->updateMousePositions();
    this->updateInput(dt);
    this->player->update(dt);
}

void GameState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->window;
    }
    this->player->render(target);
}