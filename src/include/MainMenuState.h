//
// Created by okke on 23.04.21.
//

#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"

class MainMenuState :
        public State {

private:
    //Variables
    sf::Texture bgTexture;
    float centerWidth;
    float centerHeight;
    sf::RectangleShape background;
    //Fonts
    sf::Font arial;
    sf::Font commando;

    //Buttons
    std::map<std::string, Button*> buttons;
    //Functions
    void initVariables();
    void initBackground();
    void initFonts();

    void initKeybinds();

    void initButtons();

public:
    MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State*> *states);

    virtual ~MainMenuState();

    //Functions
    void updateInput(const float &dt);

    void updateButtons();

    void update(const float &dt);

    void renderButtons(sf::RenderTarget *target = nullptr);

    void render(sf::RenderTarget *target = nullptr);

};


#endif