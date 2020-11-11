#include "client.h"

sf::TcpSocket client;

void clientStart()
{
    
    printf("running client...\n");
    sf::Socket::Status status = client.connect(sf::IpAddress::getLocalAddress(), 8889);
    if (status != sf::Socket::Done) {
        printf("Server connection failed...\n");
        return;
    } else {
        printf("Client connected\n");
    }

    sf::Packet packet;
    int x = 256;
    sf::String str = "marton sucks\n";
    packet << str;
    printf("packet conaints %zd bytes of data\n", packet.getDataSize());
    sf::Socket::Status sendStatus = client.send(packet);
    if (sendStatus == sf::Socket::Done) {
        printf("packet send %zd bytes, is data left ?: %d \n", packet.getDataSize(), packet.endOfPacket());
    } else if (sendStatus == sf::Socket::Partial) {
        printf("partially send, is data left ? : %d\n", packet.endOfPacket());
    } else if (sendStatus == sf::Socket::Error) {
        printf("an error occured during send");
    }

    client.setBlocking(false);
    sf::Packet recPacket;
    sf::String recStr = "";
    client.receive(recPacket);

}

void clientDisconnect()
{
    client.disconnect();
}