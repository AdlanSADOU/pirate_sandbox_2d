#pragma once

#include "SFML/System.hpp"
#include "SFML/Network.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>

#define AXIS "A"
#define ID "I"


class Client
{
public:
    sf::TcpSocket *socket;
    int id = 0;

    Client() {};

    Client(sf::TcpSocket *m_socket, int m_ID) {
        this->socket = m_socket;
        this->id = m_ID;
        this->SendId();
    }

    void SendId() {
        sf::Packet packet;

        packet << static_cast<sf::String>(ID);
        packet << this->id;
        this->socket->send(packet);
    }
};