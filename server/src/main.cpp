#include "server.h"

sf::TcpListener listener;
std::vector<Client> clients;
sf::SocketSelector selector;
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

    listener.listen(8889);
    selector.add(listener);
    int IDs = 0;
    sf::Int32 rate = 4;
    rateClock.restart();

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
                    printf("client with ID %d connected\n", tmpClient.id);

                    clients.push_back(tmpClient);
                    selector.add(*clientSocket);
                    
                    // tell other clients that someone just connected
                    if (clients.size() > 1)
                    {
                        for (size_t i = 0; i < clients.size(); i++)
                        {
                            if (clients[i].id == tmpClient.id)
                                continue;
                            
                        }
                    }
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
                    RpcType type;

                    Client m_client;
                    m_client = (clients[i]);

                    if (selector.isReady(*m_client.socket))
                    {

                        if ((*m_client.socket).receive(packet) == sf::Socket::Done)
                        {
                            sf::Int8 pType;
                            packet >> pType;

                            // printf("Client said: %s\n", str.toAnsiString().c_str());
                            // messageType = *str.toAnsiString().c_str();
                            //printf("packet type: %c from client n° %d ", messageType, m_client.id);

                            switch (pType)
                            {
                            case RpcType::PLAYER_AXIS:
                                receivePlayerAxis(packet);

                                for (size_t i = 0; i < clients.size(); i++)
                                {
                                    if (clients[i].id == m_client.id)
                                        continue;
                                    if (rateClock.getElapsedTime().asMilliseconds() > rate)
                                    {
                                        printf("sending data from client %d to client %d\n", m_client.id, clients[i].id);
                                        packet << (sf::Int32)m_client.id;
                                        clients[i].socket->send(packet);
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
                    }
                }
                // client 0
            }
        }
    }

    system("PAUSE");
    return 0;
}
