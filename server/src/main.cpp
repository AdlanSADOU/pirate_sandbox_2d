#include "server.h"

std::vector<sf::TcpSocket *> clients;

sf::TcpSocket serverSocket;
sf::TcpListener server;

int main(int argc, char const *argv[])
{
    printf("server starting ...\n");
    // std::cout << "Local IP: " << sf::IpAddress::getLocalAddress().toString() << std::endl;
    // printf("Public IP: %s\n", sf::IpAddress::getPublicAddress().toString());

    

    sf::TcpSocket tmpClient;
    while (1)
     {
        printf("Waiting for client connection...\n");
        if (server.listen(8889) == sf::Socket::Done) {
            sf::Socket::Status clientStatus;
            clientStatus = server.accept(tmpClient);

            switch (clientStatus) {
            case sf::Socket::Done:
                printf("client connected\n");
                clients.push_back(&tmpClient);
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

        sf::Packet packet;
        if (clients[0]->receive(packet) == sf::Socket::Done) {
            sf::String str = "";
            packet >> str;
            // std::cout << str.toWideString().c_str() << std::endl;
            printf("Client said: %s\n", str.toAnsiString().c_str());
        }
    }

    system("PAUSE");
    return 0;
}
