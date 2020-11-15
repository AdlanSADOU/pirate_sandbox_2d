#include "server.h"

sf::UdpSocket serverSocket;
std::vector<Client> clients;
sf::Clock rateClock;

sf::Int32 rate = 300;
bool running = true;
sf::Int32 IDs = 0;

void receivePlayerAxis(sf::Packet &packet)
{
    // printf("received axis\n");

    sf::Int32 x;
    sf::Int32 y;
    packet >> x >> y;
    // printf("player (%d, %d) ", x, y);
}

void Route(
    Client remoteClient,
    sf::IpAddress remoteClientIp,
    sf::Packet remoteClientPacket,
    unsigned short remoteClientPort)
{
    sf::Int8 rpcType;
    sf::Int32 remoteClientId = -1;
    remoteClientPacket >> rpcType >> remoteClientId;

    switch (rpcType)
    {
    case RpcType::CONNECT:

        remoteClient = Client(remoteClientIp, remoteClientPort, serverSocket, IDs++);
        printf("client with ID %d connected\n", remoteClient.id);

        clients.push_back(remoteClient);
        // selector.add(*remoteClient.socket);

        if (clients.size() > 1)
        {
            for (size_t i = 0; i < clients.size(); i++)
            {
                if (clients[i].id != remoteClient.id)
                    clients[i].SendRemoteClientId(IDs);
            }
        }
        break;

    case RpcType::PLAYER_AXIS:

        receivePlayerAxis(remoteClientPacket);

        for (size_t i = 0; i < clients.size(); i++)
        {
            if (clients[i].id != remoteClient.id)
            if (rateClock.getElapsedTime().asMilliseconds() > rate)
            {
                printf("sending data from client %d to client %d\n", remoteClient.id, clients[i].id);
                serverSocket.send(remoteClientPacket, clients[i].ip, clients[i].port);
                rateClock.restart();
            }
        }
        break;

    default:
        break;
    }
}

int main(int argc, char const *argv[])
{
    printf("server starting ...\n");
    printf("Local IP : %s\n", sf::IpAddress::getLocalAddress().toString().c_str());
    printf("Public IP: %s\n", sf::IpAddress::getPublicAddress().toString().c_str());

    sf::TcpSocket remoteClient;
    sf::Socket::Status clientStatus;

    serverSocket.bind(8889, sf::IpAddress::getLocalAddress());
    rateClock.restart();

    while (running)
    {
        Client remoteClient;
        sf::IpAddress remoteClientIp;
        sf::Packet remoteClientPacket;
        unsigned short remoteClientPort;

        if (serverSocket.receive(remoteClientPacket, remoteClientIp, remoteClientPort) == sf::Socket::Done)
        {
            Route(remoteClient, remoteClientIp, remoteClientPacket, remoteClientPort);
        }
    }

    system("PAUSE");
    return 0;
}
