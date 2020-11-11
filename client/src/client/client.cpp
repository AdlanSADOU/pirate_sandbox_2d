#include "client.h"

sf::TcpSocket client;

void startClient()
{
    printf("running client...\n");
    sf::Socket::Status status = client.connect(sf::IpAddress::getLocalAddress(), 8889);
    if (status != sf::Socket::Done) {
        printf("Server connection failed...\n");
    } else {
        printf("Client connected\n");
    }

    

}