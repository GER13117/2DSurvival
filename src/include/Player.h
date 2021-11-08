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
    //Initializers
    void initVariables();
    NetworkComponent *networkComponent;

    void initComponents();

public:
    Player(float x, float y, sf::Texture &texture_sheet);

    void createNetworkComponent();

    virtual ~Player();

    //Functions
    virtual void update(const float &dt);

};

#endif //INC_2DSURVIVAL_PLAYER_H