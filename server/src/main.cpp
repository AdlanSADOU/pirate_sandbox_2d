#include "server.h"

std::vector<sf::TcpSocket *> clients;

// sf::TcpSocket serverSocket;
sf::TcpListener server;

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
    server.setBlocking(true);
    printf("server starting ...\n");
    std::cout << "Local IP: " << sf::IpAddress::getLocalAddress().toString() << std::endl;
    printf("Public IP: %s\n", sf::IpAddress::getPublicAddress().toString().c_str());

    sf::TcpSocket tmpClient;
    sf::Socket::Status clientStatus;
    
    printf("Waiting for client connection...\n");
    if (server.listen(8889, sf::IpAddress::getLocalAddress()) == sf::Socket::Done)
    {
        clientStatus = server.accept(tmpClient);
        printf("client connected\n");
    }

    while (1)
    {
        sf::Packet packet;

        switch (clientStatus)
        {
        case sf::Socket::Done:
            clients.push_back(&tmpClient);
            if (clients[0]->receive(packet) == sf::Socket::Done)
            {
                sf::String str = "";
                packet >> str;

                // printf("Client said: %s\n", str.toAnsiString().c_str());
                char c = *str.toAnsiString().c_str();

                switch (c)
                {
                case 'A':
                    receivePlayerAxis(packet);
                    break;

                default:
                    break;
                }
            }
            break;

        case sf::Socket::Partial:
            printf("client partial\n");
            break;

        case sf::Socket::Disconnected:
            printf("client disconnected\n");
            break;

        default:
            break;
        }
    }

    system("PAUSE");
    return 0;
}
