#include "server.h"

sf::UdpSocket serverSocket;
std::vector<Client> clients;
sf::Clock rateClock;

bool running = true;

void receivePlayerAxis(sf::Packet &packet)
{
    // printf("received axis\n");

    sf::Int32 x;
    sf::Int32 y;
    packet >> x >> y;
    // printf("player (%d, %d) ", x, y);
}

int main(int argc, char const *argv[])
{
    printf("server starting ...\n");
    printf("Local IP : %s\n", sf::IpAddress::getLocalAddress().toString().c_str());
    printf("Public IP: %s\n", sf::IpAddress::getPublicAddress().toString().c_str());

    sf::TcpSocket tmpClient;
    sf::Socket::Status clientStatus;

    serverSocket.bind(8889, sf::IpAddress::getLocalAddress());
    sf::Int32 IDs = 0;
    sf::Int32 rate = 4;
    rateClock.restart();

    while (running)
    {
        Client tmpClient;
        sf::IpAddress remoteClientIp;
        sf::Packet remoteClientPacket;
        unsigned short remoteClientPort;
        
        if (serverSocket.receive(remoteClientPacket, remoteClientIp, remoteClientPort) == sf::Socket::Done)
        {
            sf::Int8 rpcType;
            remoteClientPacket >> rpcType;

            switch (rpcType)
            {
            case RpcType::CONNECT:
                tmpClient = Client(remoteClientIp, remoteClientPort, serverSocket, IDs++);
                printf("client with ID %d connected\n", tmpClient.id);

                clients.push_back(tmpClient);
                // selector.add(*tmpClient.socket);

                if (clients.size() > 1)
                {
                    for (size_t i = 0; i < clients.size(); i++)
                    {
                        if (clients[i].id == tmpClient.id)
                            continue;
                        clients[i].SendRemoteClientId(IDs);
                    }
                }
                break;

            case RpcType::PLAYER_AXIS:
                receivePlayerAxis(remoteClientPacket);

                for (size_t i = 0; i < clients.size(); i++)
                {
                    if (clients[i].id == tmpClient.id)
                        continue;
                    if (rateClock.getElapsedTime().asMilliseconds() > rate)
                    {
                        printf("sending data from client %d to client %d\n", tmpClient.id, clients[i].id);
                        remoteClientPacket << (sf::Int32)tmpClient.id;
                        serverSocket.send(remoteClientPacket, clients[i].ip, clients[i].port);
                        rateClock.restart();
                    }
                    {
                        //printf("time %d < rate %d\n", rateClock.getElapsedTime().asMilliseconds(), rate);
                    }
                }
                break;

            default:
                break;
            }
        }
        else
        {
        }
    }

    system("PAUSE");
    return 0;
}
