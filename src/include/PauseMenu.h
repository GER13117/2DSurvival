//
// Created by Okke on 20.12.2021.
//

#ifndef INC_2DSURVIVAL_PauseMenu_H
#define INC_2DSURVIVAL_PauseMenu_H

#include "Button.h"
#include <map>
//#include "MainMenuState.h"

class PauseMenu {
private:
    float centerWidth;
    float centerHeight;
    sf::Vector2f canvasSize;
    sf::Vector2f canvasPos;
    sf::RectangleShape mainShape;
    std::map<std::string, Button *> buttons;

    void initButtons();

public:
    PauseMenu(sf::Vector2f pos, sf::Vector2f size);

    virtual ~PauseMenu();

    void renderButtons(sf::RenderTarget &target);

    void update(sf::Vector2f mousePos);

    void render(sf::RenderTarget &target);

};


#endif //INC_2DSURVIVAL_PauseMenu_H
