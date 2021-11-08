//
// Created by okke on 08.11.21.
//

#include "include/NetworkComponent.h"

void NetworkComponent::initVariables() {

    std::signal(SIGTERM, signal_handler);

    //ServerIp = sf::IpAddress::LocalHost; //MacbookPro IP
    //ServerPort = 55000;
}

// Extension Allowing sf::Vector2f to be sent with Packets
inline sf::Packet &operator<<(sf::Packet &packet, const sf::Vector2f &p) {
    return packet << p.x << p.y;;
}

inline sf::Packet &operator>>(sf::Packet &packet, sf::Vector2f &p) {
    return packet >> p.x >> p.y;
}

/*
void NetworkComponent::sendText() {
    std::cout << "Ready to send messages...\n";

    auto state = CommunicationState::Send;

    while (running) {
        if (state == CommunicationState::Send) {
            auto message = ""s;
            std::getline(std::cin, message);
            auto packet = sf::Packet{};
            packet << message;

            if (socket.send(packet, ServerIp, ServerPort) == sf::Socket::Done) {
                std::cout << "== Sending (" << ServerIp.toString() << ":" << ServerPort << ") ==\n";
                std::cout << message << "\n";
                state = CommunicationState::Receive;
            } else {
                std::cerr << "Error sending to " << ServerIp.toString() << ":" << ServerPort << "\n";
                sf::sleep(sf::milliseconds(100));
            }
        } else {
            auto packet = sf::Packet{};
            auto ipAddress = sf::IpAddress{};
            unsigned short port = 0;
            if (socket.receive(packet, ipAddress, port) == sf::Socket::Done) {
                auto message = ""s;
                packet >> message;
                std::cout << "== Received (" << ipAddress.toString() << ":" << port << ") ==\n";
                std::cout << message << "\n";
                state = CommunicationState::Send;
            } else {
                sf::sleep(sf::milliseconds(100));
            }
        }

    }
}*/

void NetworkComponent::sendPosition(sf::Vector2f pos) {
    const sf::IpAddress ServerIp = sf::IpAddress::LocalHost;
    const unsigned short ServerPort = 55000;

    auto socket = sf::UdpSocket{};

    auto packet = sf::Packet{};

    //std::cout << "Ready to send messages...\n";
    packet << pos;

    if (socket.send(packet, ServerIp, ServerPort) == sf::Socket::Done) {
        //std::cout << "== Sending (" << ServerIp.toString() << ":" << ServerPort << ") ==\n";
        //std::cout << pos.x << " " << pos.y << "\n";
    } else {
        //std::cerr << "Error sending to " << ServerIp.toString() << ":" << ServerPort << "\n";
        sf::sleep(sf::milliseconds(100));
    }
}


NetworkComponent::NetworkComponent() {
    initVariables();
}

NetworkComponent::~NetworkComponent() {

}

