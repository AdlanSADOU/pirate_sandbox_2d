#pragma once

#include "SFML/System.hpp"
#include "SFML/Network.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>


typedef enum RemoteProcedureCallType {
    PLAYER_AXIS,
    PLAYER_ID,
    REMOTE_ID,

} RpcType;

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

        packet << static_cast<sf::Uint8>(RpcType::REMOTE_ID);
        packet << this->id;
        this->socket->send(packet);
    }

    void SendRemoteClientId(int m_id) {
        sf::Packet packet;

        packet << static_cast<sf::Uint8>(RpcType::PLAYER_ID);
        packet << m_id;
        this->socket->send(packet);
    }
};