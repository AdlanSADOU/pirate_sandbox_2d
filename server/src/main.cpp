#include "server.h"

sf::TcpSocket socket;
sf::TcpListener server;

int main(int argc, char const *argv[])
{
    printf("server starting ...\n");

    // socket.setBlocking(false);
    // sf::Socket::Status status = socket.connect(sf::IpAddress::LocalHost, 8889);
    // if (status != sf::Socket::Done) {
    //     printf("count not connect\n");
    // }

    while (1) {
        printf("Wainting for client connection...\n");
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
