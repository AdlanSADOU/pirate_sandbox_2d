#include "server.h"

sf::TcpListener listener;
std::vector<Client> clients;
sf::SocketSelector selector;

bool running = true;

void receivePlayerAxis(sf::Packet &packet)
{
    // printf("received axis\n");

    sf::String str;
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
    int IDs = 0;

    while (running)
    {
        if (selector.wait())
        {
            if (selector.isReady(listener))
            {
                sf::TcpSocket *clientSocket = new sf::TcpSocket;
                if (listener.accept(*clientSocket) == sf::Socket::Done)
                {
                    Client tmpClient = Client(clientSocket, IDs++);
                    printf("client n° %d connected\n", tmpClient.id);

                    clients.push_back(tmpClient);
                    selector.add(*clientSocket);
                    
                }
                else
                {
                    delete clientSocket;
                }
            }
            else
            {

                for (size_t i = 0; i < clients.size(); i++)
                {
                    sf::Packet packet;
                    char messageType;
                    Client m_client;
                    m_client = (clients[i]);

                    if (selector.isReady(*m_client.socket))
                    {

                        if ((*m_client.socket).receive(packet) == sf::Socket::Done)
                        {
                            sf::String str = "";
                            packet >> str;

                            // printf("Client said: %s\n", str.toAnsiString().c_str());
                            messageType = *str.toAnsiString().c_str();
                            //printf("packet type: %c from client n° %d ", messageType, m_client.id);

                            switch (messageType)
                            {
                            case 'A':
                                receivePlayerAxis(packet);
                                for (size_t i = 0; i < clients.size(); i++)
                                {
                                    if (clients[i].id == m_client.id)
                                        continue;
                                    printf("sending data from client %d to client %d\n", m_client.id, clients[i].id);
                                    packet << (sf::Int32)m_client.id;
                                    clients[i].socket->send(packet);
                                }
                                break;

                            default:
                                break;
                            }
                        }
                    }
                }
                // client 0
            }
        }
    }

    system("PAUSE");
    return 0;
}
