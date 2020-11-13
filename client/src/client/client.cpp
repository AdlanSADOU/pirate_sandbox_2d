#include "client.h"

sf::TcpSocket client;

void receivePlayerAxis(sf::Packet &packet)
{
    // printf("received axis\n");

    sf::String str;
    sf::Int32 x;
    sf::Int32 y;
    packet >> x >> y;
    printf("player (%d, %d)\n", x, y);
}

void clientStart()
{

    printf("running client...\n");
    sf::Socket::Status status = client.connect(sf::IpAddress::getLocalAddress(), 8889);
    if (status != sf::Socket::Done)
    {
        printf("Server connection failed...\n");
        return;
    }
    else
    {
        printf("Connected to server\n");
    }

    // sf::Packet packet;
    // int x = 256;
    // sf::String str = "marton sucks\n";
    // packet << str;
    // printf("packet conaints %zd bytes of data\n", packet.getDataSize());
    // sf::Socket::Status sendStatus = client.send(packet);
    // if (sendStatus == sf::Socket::Done) {
    //     printf("packet send %zd bytes, is data left ?: %d \n", packet.getDataSize(), packet.endOfPacket());
    // } else if (sendStatus == sf::Socket::Partial) {
    //     printf("partially send, is data left ? : %d\n", packet.endOfPacket());
    // } else if (sendStatus == sf::Socket::Error) {
    //     printf("an error occured during send");
    // }

    client.setBlocking(false);
    sf::Packet recPacket;
    sf::String recStr = "";
    client.receive(recPacket);
}

void clientRoute()
{
    sf::Packet packet;
    char messageType;

    if (client.receive(packet) == sf::Socket::Done)
    {
        sf::String str = "";
        packet >> str;

        // printf("Client said: %s\n", str.toAnsiString().c_str());
        messageType = *str.toAnsiString().c_str();
        printf("packet type: %c ", messageType);

        switch (messageType)
        {
        case 'A':
            receivePlayerAxis(packet);
            break;

        default:
            break;
        }
    }
}

void clientDisconnect()
{
    client.disconnect();
}

void clientSendPlayerAxis(sf::Int32 x, sf::Int32 y)
{
    sf::Packet packet;
    sf::String str = "A";
    packet << str << x << y;

    sf::String tstr;
    sf::Int32 tx;
    sf::Int32 ty;

    packet >> str >> tx >> ty;

    // printf("%s %d %d\n", str.toAnsiString().c_str(), tx, ty);

    // printf("packet conaints %zd bytes of data\n", packet.getDataSize());
    sf::Socket::Status sendStatus = client.send(packet);
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
        printf("an error occured during send");
    }
}