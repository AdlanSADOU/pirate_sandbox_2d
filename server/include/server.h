#pragma once

#include "SFML/System.hpp"
#include "SFML/Network.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>


typedef enum RemoteProcedureCallType {
    CONNECT,
    PLAYER_AXIS,
    PLAYER_ID,
    REMOTE_ID,

} RpcType;

class Client
{
public:
    sf::UdpSocket *serverSocket;
    sf::IpAddress ip;
    unsigned short port;

    int id = 0;

    Client() {};

    Client(sf::IpAddress m_ip, unsigned int m_port, sf::UdpSocket &m_serverSocket, int m_ID) {
        // this->socket->bind(m_port, m_ip);
        this->ip = m_ip;
        this->port = m_port;
        this->serverSocket = &m_serverSocket;
        this->id = m_ID;
        this->SendId();
    }

    void SendId() {
        sf::Packet packet;

        packet << static_cast<sf::Uint8>(RpcType::PLAYER_ID);
        packet << this->id;
        this->serverSocket->send(packet, this->ip, this->port);
    }

    void SendRemoteClientId(int m_id) {
        sf::Packet packet;

        packet << static_cast<sf::Uint8>(RpcType::REMOTE_ID);
        packet << m_id;
        this->serverSocket->send(packet, this->ip, this->port);
    }
};