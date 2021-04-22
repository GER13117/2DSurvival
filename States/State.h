//
// Created by okke on 22.04.21.
//
#ifndef STATE_H
#define STATE_H

#include "../Entities/Entity.h"

class State {
protected:
    sf::RenderWindow *window;
    std::vector<sf::Texture> texture;
    bool quit;
public:
    State(sf::RenderWindow *window);

    virtual ~State();

    const bool &getQuit() const;

    virtual void checkForQuit();

    virtual void endState() = 0;

    virtual void updateKeybinds(const float &dt) = 0;

    virtual void update(const float &dt) = 0;

    virtual void render(sf::RenderTarget *target = nullptr) = 0;
};


#endif
