//
// Created by okke on 22.04.21.
//
#include "include/GameState.h"

void GameState::initRenderTexture() {
    if (!renderTexture.create(this->window->getSize().x, this->window->getSize().y))
        throw std::runtime_error("ERROR::GAMESTATE::INITRENDERTEXTURES::COULD NOT CREATE RENDERTEXTURE");
    this->renderSprite.setTexture(this->renderTexture.getTexture());

}

void GameState::initView() {
    float height = 900;
    this->view.setSize(this->window->getSize().x * height / this->window->getSize().y, height);
    this->view.setCenter(sf::Vector2f{0.f, 0.f});
    this->viewWindowRatio = height / this->window->getSize().y;
    std::cout << "x: " << window->getSize().x << " y:  " << window->getSize().y
              << std::endl; //Debugging because on macBook Pro wrong display resolution is used
    std::cout << "x: " << view.getSize().x << " y:  " << view.getSize().y << " ratio: "
              << height / this->window->getSize().y
              << std::endl; //Debugging to check if the view gets made correctly
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
        throw std::runtime_error("ERROR::GAMESTATE::INITTEXTURES::COULD NOT LOAD TestSpriteSheet.png");

    if (!this->textures["TILEMAP_SHEET"].loadFromFile("../resources/Pictures/TileSheets/TerrainSprite.png"))
        throw std::runtime_error("ERROR::GAMESTATE::INITTEXTURES::COULD NOT LOAD TerrainSprite.png");
}

void GameState::initShader() {
    if (!coreShader.loadFromFile("../shaders/vertex_shader.vert", "../shaders/fragment_shader.frag"))
        std::cout << "Could not load shader" << std::endl;
}


void GameState::initTilemap() {
    tileSize = 16;
    auto maxTilesX = (uint8_t) (this->view.getSize().x / (float) tileSize) / 2 + 3;
    auto maxTilesY = (uint8_t) (this->view.getSize().y / (float) tileSize) / 2 + 4;
    this->tileMap = new TileMap(this->textures["TILEMAP_SHEET"], tileSize, tileSize, sf::Vector2f(0.f, 0.f), maxTilesX, maxTilesY);
}

void GameState::initPLayers() {
    playerWidth = 32;
    playerHeight = 48;
    this->player = new Player(0, 0, (int) playerWidth, (int) playerHeight, this->textures["PLAYER_SHEET"]);
}

void GameState::initPauseMenu() {
    sf::Vector2f size = {200.f, 200.f};
    this->pauseMenu = new PauseMenu(
            {this->window->getSize().x / 2.f - size.x / 2.f, this->window->getSize().y / 2.f - size.y / 2.f}, size);
}

/**
 * Constructor of GameState. Calls the different init-funtions
 * @param window pointer to the RenderWindow
 * @param supportedKeys map of the supported keys (string, int)
 * @param states stack of the different States (as pointers)
 * @param commando commando font (will be replaced at some point)
 */
GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states,
                     const sf::Font &commando)
        : State(window, supportedKeys, states) {
    this->font = commando;
    this->initShader();
    this->initRenderTexture();
    this->initView();
    this->initKeybinds();
    this->initTextures();
    this->initTilemap();
    this->initPLayers();
    this->initPauseMenu();
    this->initInfoText();
}

/**
 * Destructor of GameState
 */
GameState::~GameState() {
    delete this->player;
    delete this->tileMap;
    delete this->pauseMenu;
}

/**
 * updates the input and calls according functions
 * @param dt Delta Time (time between the frames)
 */
void GameState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
        this->player->move(-1.f, 0.f, dt, this->tileMap->structuresInScreen);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
        this->player->move(1.f, 0.f, dt, this->tileMap->structuresInScreen);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
        this->player->move(0.f, 1.f, dt, this->tileMap->structuresInScreen);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
        this->player->move(0.f, -1.f, dt, this->tileMap->structuresInScreen);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("PAUSE_MENU")))) {
        showPauseMenu = true; //Used to open the PauseMenu
        this->endState();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        tileMap->createPlayerStructure(
                {static_cast<float>(static_cast<int>((mousePosView.x * viewWindowRatio + player->getPosition().x -
                                                      this->view.getSize().x / 2 + (float) tileSize) /
                                                     (float) tileSize) * tileSize),
                 static_cast<float>(static_cast<int>((mousePosView.y * viewWindowRatio + player->getPosition().y -
                                                      this->view.getSize().y / 2 + (float) tileSize) /
                                                     (float) tileSize) * tileSize)}, {16, 16},
                sf::Color(139, 69, 19));
}

/**
 * centers the view (camera) on the player
 */
void GameState::updateView() {
    this->view.setCenter(sf::Vector2f{this->player->getPosition().x + playerWidth / 2,
                                      this->player->getPosition().y + playerHeight / 2});
}

/**
 * calls the different update functions in GameState
 * @param dt Delta Time (time between the frames)
 */
void GameState::update(const float &dt) {
    this->updateMousePositions();
    this->updateInput(dt);
    this->tileMap->update(this->player->getPosition());
    this->player->update(dt);
    this->updateView();
    this->fps = 1.f / dt;
    this->fpsText.setString(std::to_string((int) fps));
    this->playerPos.setString("x: " + std::to_string(this->player->getPosition().x) + " y: " +
                              std::to_string(this->player->getPosition().y));

    /*
     * this->updateMousePositions();
    this->updateInput(dt);
    this->pool.push_task([this] {
        this->tileMap->update(this->player->getPosition());
    });
    this->pool.push_task([this, &dt] {
        this->player->update(dt);
        this->updateView();
    });

    this->pool.push_task([this, &dt] {
        this->fps = 1.f / dt;
        this->fpsText.setString(std::to_string((int) fps));
        this->playerPos.setString("x: " + std::to_string(this->player->getPosition().x) + " y: " +
                                  std::to_string(this->player->getPosition().y));
    });

    pool.wait_for_tasks();
     */
}

void GameState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->window;
    }
    this->renderTexture.clear(sf::Color::Black);
    this->renderTexture.setView(this->view);

    //Sachen die gemalt werden sollen
    this->tileMap->render(this->renderTexture);
    this->player->render(this->renderTexture, false);

    this->renderTexture.display();

    target->draw(this->renderSprite);
    target->draw(this->fpsText);
    target->draw(this->playerPos);

    if (showPauseMenu) {
        pauseMenu->render(*target);
    }
}

/**
 * initializes the font, color and size of the text that displays the info-text
 */
void GameState::initInfoText() {
    this->fpsText.setFillColor(sf::Color::White);
    this->fpsText.setCharacterSize(12);
    this->fpsText.setFont(this->font);
    this->fpsText.setPosition({10.f, 10.f});
    this->playerPos.setFillColor(sf::Color::White);
    this->playerPos.setCharacterSize(12);
    this->playerPos.setFont(this->font);
    this->playerPos.setPosition({10.f, 25.f});
}