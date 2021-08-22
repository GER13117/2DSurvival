//
// Created by okke on 22.04.21.
//
#ifndef STATE_H
#define STATE_H

#include "Player.h"

class State {
protected:
    std::stack<State *> *states;
    sf::RenderWindow *window;
    std::map<std::string, int> *supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    std::map<std::string, sf::Texture> textures;

    //Initializers
    virtual void initKeybinds() = 0;

public:
    State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);

    virtual ~State();

    const bool &getQuit() const;

    void endState();

    virtual void updateMousePositions();

    virtual void updateInput(const float &dt) = 0;

    virtual void update(const float &dt) = 0;

    virtual void render(sf::RenderTarget *target = nullptr) = 0;
};

#endif