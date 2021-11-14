//
// Created by okke on 08.11.21.
//
#ifndef INC_2DSURVIVAL_NETWORKCOMPONENT_H
#define INC_2DSURVIVAL_NETWORKCOMPONENT_H

#include <SFML/Network.hpp>

#include <iostream>
#include <csignal>
#include <atomic>
#include <string>

using namespace std::string_literals;
namespace {
    volatile std::atomic<bool> running = true;

    void signal_handler(int) {
        running = false;
    }

    enum class CommunicationState {
        Send,
        Receive
    };
}
class NetworkComponent {
private:
    void initVariables();

    void sendText();

public:
    static void sendPosition(sf::Vector2f pos);

    NetworkComponent();

    virtual ~NetworkComponent();
};

#endif //INC_2DSURVIVAL_NETWORKCOMPONENT_H
