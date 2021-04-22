//
// Created by okke on 22.04.21.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState :

        public State {
private:
    Entity player;
public:

    GameState(sf::RenderWindow *window);

    virtual ~GameState();

    //Functions
    void endState();

    void updateKeybinds(const float &dt);

    void update(const float &dt);

    void render(sf::RenderTarget *target = nullptr);

};


#endif