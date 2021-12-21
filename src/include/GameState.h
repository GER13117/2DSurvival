//
// Created by okke on 22.04.21.
//
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Tile.h"
#include "TileMap.h"
#include "PauseMenu.h"
class GameState :
        public State {
private:
    float playerWidth;
    float playerHeight;
    bool showPauseMenu = false;
    sf::View view;
    sf::RectangleShape testRect;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;
    PauseMenu *pauseMenu;
    Player *player;
    TileMap *tileMap;
    float fps{};
    sf::Text fpsText;
    sf::Text playerPos;
    sf::Font font;

    //Functions
    void initView();

    void initPauseMenu();

    void initInfoText();

    void initRenderTexture(); //Rename??

    void initKeybinds();

    void initTextures();

    void initTilemap();

    void initPLayers();

public:
    GameState(sf::RenderWindow *window,
              std::map<std::string, int> *supportedKeys, std::stack<State *> *states, const sf::Font& commando);

    virtual ~GameState();

    //Functions
    void updateInput(const float &dt);

    void updateView();

    void update(const float &dt);

    void render(sf::RenderTarget *target = nullptr);
};

#endif