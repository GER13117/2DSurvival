//
// Created by okke on 22.04.21.
//
#include "include/GameState.h"

void GameState::initRenderTexture() {
    renderTexture.create(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height); //TODO: Get size of the window
    this->renderSprite.setTexture(this->renderTexture.getTexture());

}

void GameState::initView() {
    //this->view.reset(sf::FloatRect(0.f, 0.f, 300.f, 200.f));
    this->view.setSize(sf::Vector2f{static_cast<float>(sf::VideoMode::getDesktopMode().width)/2.f, static_cast<float>(sf::VideoMode::getDesktopMode().height)/2.f});
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
    this->player = new Player(0, 0, &this->textures["PLAYER_IDLE"]);
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

void GameState::updateView(const float &dt) {
    //this->view.setCenter(std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y)); //TODO: Fix "wobble"
}

void GameState::update(const float &dt) {
    this->updateMousePositions();
    this->updateInput(dt);
    this->player->update(dt);
    this->updateView(dt);
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