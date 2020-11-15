#include "client.h"

sf::IpAddress gServerIP;
unsigned short gServerPort;

void Client::DrawRemotePlayers()
{
    gWindow->draw(*remotePlayers[0]->sprite);
}

void Client::ReceiveRemotePlayerAxis(sf::Packet &packet)
{
    sf::Int32 remoteClientId;
    float posX;
    float posY;
    float axeX;
    float axeY;

    packet >> remoteClientId >> axeX >> axeY >> posX >> posY;
    remotePlayers[0]->SetPosition({posX, posY});
    remotePlayers[0]->Move(axeX, axeY);
    printf("Axis (%f, %f)", axeX, axeY);
    printf("from player %d\n", remoteClientId);
}

void Client::SendPlayerAxis(float axeX, float axeY, float posX, float posY)
{
    sf::Packet packet;
    sf::Int8 rpc = RpcType::PLAYER_AXIS;

    packet << rpc << Client::myId << axeX << axeY << posX << posY;
    SendPacket(packet);
}

/////////////////////////////////////////////////////////////////////////
/// CLIENT START
void Client::Start()
{
    remotePlayers.push_back(new Entity("assets/PlayerRed_Frame_01_png_processed.png"));

    // before doing this, server must send  remote clients positions
    remotePlayers[0]->SetPosition({400, 300});

    printf("running client...\n");
    sf::Packet packet;
    packet << RpcType::CONNECT;

    sf::Socket::Status status = client.send(packet, sf::IpAddress::getLocalAddress(), 8889);
    if (status != sf::Socket::Done)
    {
        printf("Server connection failed...\n");
        return;
    }
    else
    {
        printf("Connected to server\n");
    }

    client.setBlocking(false);
}

void Client::Route()
{
    sf::Packet packet;
    sf::IpAddress serverIP;
    unsigned short serverPort;

    if (client.receive(packet, serverIP, serverPort) == sf::Socket::Done)
    {
        sf::Int8 type;
        packet >> type;

        switch (type)
        {
        case RpcType::PLAYER_AXIS:
            ReceiveRemotePlayerAxis(packet);
            break;
        case RpcType::PLAYER_ID:
            sf::Int32 myId;
            packet >> myId;
            Client::myId = myId;
            gServerIP = serverIP;
            gServerPort = serverPort;
            printf("received myId %d\n", myId);
            break;
        case RpcType::REMOTE_ID:
            sf::Int32 remoteClientId;
            packet >> remoteClientId;
            printf("player %d is near\n", remoteClientId);
            break;

        default:
            break;
        }
    }
}

void Client::SendPacket(sf::Packet &packet)
{

    sf::Socket::Status sendStatus = client.send(packet, gServerIP, gServerPort);

    if (sendStatus == sf::Socket::Done)
    {
        //printf("packet send %zd bytes, is data left ?: %d \n", packet.getDataSize(), packet.endOfPacket());
    }
    else if (sendStatus == sf::Socket::Partial)
    {
        printf("partially send, is data left ? : %d\n", packet.endOfPacket());
    }
    else if (sendStatus == sf::Socket::Error)
    {
        printf("an error occured during send\n");
        printf("server IP: %s\nPort: %d\n", gServerIP.toString().c_str(), gServerPort);
    }
}

void Client::Disconnect()
{
}
