//
// Created by okke on 22.04.21.
//
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Tile.h"

class GameState :
        public State {
private:
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;
    Player *player;
    Tile *tile;

    //Functions
    void initView();
    void initRenderTexture(); //Rename??
    void initKeybinds();
    void initTextures();
    void initTilemap();
    void initPLayers();
public:
    GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*> *states);

    virtual ~GameState();

    //Functions
    void updateInput(const float &dt);

    void updateView(const float &dt);

    void update(const float &dt);

    void render(sf::RenderTarget *target = nullptr);
};

#endif