//
// Created by okke on 22.04.21.
//
#include "include/GameState.h"

void GameState::initRenderTexture() {
    renderTexture.create(this->window->getSize().x, this->window->getSize().y);
    this->renderSprite.setTexture(this->renderTexture.getTexture());

}

void GameState::initView() {
    this->view.setSize((float) this->window->getSize().x / 2, (float) this->window->getSize().y / 2);
    this->view.setCenter(sf::Vector2f{0.f, 0.f});
    std::cout << "x: " << window->getSize().x << " y:  " << window->getSize().y
              << std::endl; //Debugging because on laptop not the full display is used
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
        throw std::runtime_error("ERROR::GAMESTATE::INITTEXTURES::COULD NOT LOAD TEST.PNG");
}

void GameState::initTilemap() {
    uint8_t tileSize = 16;
    auto maxTilesX = (uint8_t) (this->view.getSize().x / tileSize) / 2 + 2;
    auto maxTilesY = (uint8_t) (this->view.getSize().y / tileSize) / 2 + 3;
    this->tileMap = new TileMap(tileSize, tileSize, sf::Vector2f(0.f, 0.f), maxTilesX, maxTilesY);
}

void GameState::initPLayers() {
    this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states,
                     const sf::Font &commando)
        : State(window, supportedKeys, states) {
    this->font = commando;
    this->initRenderTexture();
    this->initView();
    this->initKeybinds();
    this->initTextures();
    this->initTilemap();
    this->initPLayers();
    this->initFPS();
}

GameState::~GameState() {
    delete this->player;
    delete this->tileMap;
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
    this->tileMap->update(player->getPosition());
    this->player->update(dt);
    this->updateView(dt);
    this->fps = 1.f / dt;
}

void GameState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->window;
    }
    this->renderTexture.clear(sf::Color::Black);
    this->renderTexture.setView(this->view);

    //Sachen die gemalt werden sollen
    this->tileMap->render(this->renderTexture);
    this->player->render(this->renderTexture);

    this->renderTexture.display();
    this->fpsText.setString(std::to_string((int) fps));
    target->draw(this->renderSprite);
    target->draw(this->fpsText);
}

void GameState::initFPS() {
    this->fpsText.setFillColor(sf::Color::White);
    this->fpsText.setCharacterSize(35);
    this->fpsText.setFont(this->font);
}