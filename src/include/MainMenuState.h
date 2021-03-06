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
    float centerWidth{};
    float centerHeight{};
    sf::RectangleShape background;
    //Fonts
    sf::Font arial;
    sf::Font commando;
    sf::Font wayfarer;
    //Buttons
    std::map<std::string, Button *> buttons;

    //Functions
    void initVariables();

    void initBackground();

    void initFonts();

    void initKeybinds() override;

    void initButtons();

public:
    MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);

    virtual ~MainMenuState();

    //Functions
    void updateInput(const float &dt) override;

    void updateButtons();

    void update(const float &dt) override;

    void renderButtons(sf::RenderTarget &target);

    void render(sf::RenderTarget *target = nullptr);
};

#endif