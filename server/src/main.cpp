#include "server.h"

sf::TcpListener listener;
std::list<sf::TcpSocket *> clients;
sf::SocketSelector selector;

int id;
bool running = true;

void receivePlayerAxis(sf::Packet &packet)
{
    // printf("received axis\n");

    sf::String str;
    sf::Int32 x;
    sf::Int32 y;
    packet >> x >> y;
    printf("player (%d, %d)\n", x, y);
}

int main(int argc, char const *argv[])
{
    printf("server starting ...\n");
    printf("Local IP : %s\n", sf::IpAddress::getLocalAddress().toString().c_str());
    printf("Public IP: %s\n", sf::IpAddress::getPublicAddress().toString().c_str());

    sf::TcpSocket tmpClient;
    sf::Socket::Status clientStatus;

    // printf("Waiting for client connection...\n");
    // if (server.listen(8889, sf::IpAddress::getLocalAddress()) == sf::Socket::Done)
    // {
    //     clientStatus = server.accept(tmpClient);
    //     clientsMap.insert(std::pair<sf::TcpSocket &, int>(tmpClient, id++));
    //     selector.add(tmpClient);

    //     printf("client %d connected, IP: %s\n", clientsMap);
    // }

    listener.listen(8889);
    selector.add(listener);

    while (running)
    {
        if (selector.wait())
        {
            if (selector.isReady(listener))
            {
                // The listener is ready: there is a pending connection
                sf::TcpSocket *client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Done)
                {
                    clients.push_back(client);
                    selector.add(*client);
                }
                else
                {
                    // Error, we won't get a new connection, delete the socket
                    delete client;
                }
            }
            else
            {
                // The listener socket is not ready, test all other sockets (the clients)
                for (std::list<sf::TcpSocket *>::iterator it = clients.begin(); it != clients.end(); ++it)
                {
                    sf::TcpSocket &client = **it;
                    if (selector.isReady(client))
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
                                client.send(packet);
                                break;

                            default:
                                break;
                            }
                        }

                        
                    }
                }
            }
        }
    }

    system("PAUSE");
    return 0;
}
