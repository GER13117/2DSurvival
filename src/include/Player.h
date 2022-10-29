//
// Created by okke on 28.04.21.
//
#ifndef INC_2DSURVIVAL_PLAYER_H
#define INC_2DSURVIVAL_PLAYER_H

#include "Entity.h"

class Player :
        public Entity {
private:
    //Variables

    //Initializers
    void initVariables();

    void initComponents();

public:
    Player(float x, float y, int width, int height, sf::Texture &texture_sheet);

    virtual ~Player();

    //Functions
    void update(const float &dt, const std::vector<Tile *>& structures) override;

    void render(sf::RenderTarget &target, bool show_hitbox) override;
};

#endif //INC_2DSURVIVAL_PLAYER_H