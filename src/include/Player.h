//
// Created by okke on 28.04.21.
//

#ifndef INC_2DSURVIVAL_PLAYER_H
#define INC_2DSURVIVAL_PLAYER_H


#include "Entity.h"

class Player :
        public Entity{
private:
    //Variables
    //Initializers
    void initVariables();
    void initComponents();
public:
    Player(float x, float y, sf::Texture *texture);
    virtual ~Player();
    //Functions

};


#endif //INC_2DSURVIVAL_PLAYER_H
