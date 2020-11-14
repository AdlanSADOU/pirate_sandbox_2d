#pragma once

#include "game.h"
#include "SFML/Network.hpp"

namespace Client
{
    typedef enum RemoteProcedureCallType
    {
        CONNECT,
        PLAYER_AXIS,
        PLAYER_ID,
        REMOTE_ID,

    } RpcType;

    static sf::UdpSocket client;
    static sf::Int32 myId;
    static std::vector<Entity *> remotePlayers;

    void Start();
    void Disconnect();
    void Route();
    void SendPacket(sf::Packet &packet);
    void DrawRemotePlayers();
    void SendPlayerAxis(float x, float y);
    void ReceiveRemotePlayerAxis(sf::Packet &packet);
}; // namespace Client