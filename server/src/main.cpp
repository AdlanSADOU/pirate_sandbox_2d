#include "server.h"

sf::TcpSocket socket;

sf::TcpSocket serverSocket;
sf::TcpListener server;

int main(int argc, char const *argv[])
{
    printf("server starting ...\n");
    // std::cout << "Local IP: " << sf::IpAddress::getLocalAddress().toString() << std::endl;
    // printf("Public IP: %s\n", sf::IpAddress::getPublicAddress().toString());

    

    while (1) {
        printf("Waiting for client connection...\n");
        if (server.listen(8889) == sf::Socket::Done) {
            sf::Socket::Status clientStatus;
            clientStatus = server.accept(socket);

            switch (clientStatus) {
            case sf::Socket::Done:
                printf("client connected\n");
                break;

            case sf::Socket::Partial:
                printf("client partial\n");
                break;

            default:
                break;
            }

            
        }
    }

    system("PAUSE");
    return 0;
}
