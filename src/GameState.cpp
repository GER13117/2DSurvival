//
// Created by okke on 22.04.21.
//
#include "include/GameState.h"

void GameState::initRenderTexture() {
    renderTexture.create(this->window->getSize().x, this->window->getSize().y);
    this->renderSprite.setTexture(this->renderTexture.getTexture());

}

void GameState::initView() {
    this->view.setSize(this->window->getSize().x/2, this->window->getSize().y/2);
    this->view.setCenter(sf::Vector2f{0.f, 0.f});
}

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
    for (auto i: this->keybinds) {
        std::cout << i.first << " " << i.second << std::endl;
    }*/
}

void GameState::initTextures() {
    if (!this->textures["PLAYER_SHEET"].loadFromFile("../resources/Pictures/Entities/Player/testSpriteSheet.png"))
        throw "ERROR::GAMESTATE::INITTEXTURES::COULD NOT LOAD TEST.PNG";
}

void GameState::initPLayers() {
    this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}


GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
        : State(window, supportedKeys, states) {
    this->initRenderTexture();
    this->initView();
    this->initKeybinds();
    this->initTextures();
    this->initPLayers();
}

GameState::~GameState() {
    delete this->player;
}

void GameState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
        this->player->move(-1.f, 0.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
        this->player->move(1.f, 0.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
        this->player->move(0.f, 1.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
        this->player->move(0.f, -1.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
        this->endState();
    }
}

void GameState::updateView(const float &dt) {
    this->view.setCenter(this->player->getPosition().x, this->player->getPosition().y);
}

void GameState::update(const float &dt) {
    this->updateMousePositions();
    this->updateInput(dt);
    this->player->update(dt);
    //this->updateView(dt);
}

void GameState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->window;
    }
    this->renderTexture.clear(sf::Color::Green);
    this->renderTexture.setView(this->view);

    //Sachen die gemalt werden sollen
    this->player->render(this->renderTexture);

    this->renderTexture.display();
    target->draw(this->renderSprite);
}