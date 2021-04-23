//
// Created by okke on 23.04.21.
//

#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "../ResourceFiles/Button.h"

class MainMenuState:
        public State{

private:
    //Variables
    sf::RectangleShape background;
    //Fonts
    sf::Font arial;
    sf::Font commando;
    //Buttons
    Button *gamestate_btn;
    //Functions
    void initFonts();
    void initKeybinds();
public:
    MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys);

    virtual ~MainMenuState();

    //Functions
    void endState();

    void updateInput(const float &dt);

    void update(const float &dt);

    void render(sf::RenderTarget *target = nullptr);

};


#endif
