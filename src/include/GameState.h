//
// Created by okke on 22.04.21.
//
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState :
        public State {
private:
    Player *player;

    //Functions
    void initKeybinds();
    void initTextures();
    void initPLayers();
public:
    GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*> *states);

    virtual ~GameState();

    //Functions
    void updateInput(const float &dt);

    void update(const float &dt);

    void render(sf::RenderTarget *target = nullptr);
};

#endif