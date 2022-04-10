//
// Created by okke on 28.04.21.
//
#ifndef INC_2DSURVIVAL_PLAYER_H
#define INC_2DSURVIVAL_PLAYER_H

#include "Entity.h"
#include "NetworkComponent.h"

class Player :
        public Entity {
private:
    //Variables
    NetworkComponent *networkComponent;

    //Initializers
    void initVariables();

    void initComponents();

public:
    Player(float x, float y, int width, int height, sf::Texture &texture_sheet);

    virtual ~Player();

    //Functions
    void update(const float &dt) override;

    void render(sf::RenderTarget &target, bool show_hitbox) override;
};

#endif //INC_2DSURVIVAL_PLAYER_H