///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Network/Server.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
Server::Server(Uint16 port)
    : m_nextId(0)
{
    m_socket = ::socket(AF_INET, SOCK_STREAM, 0);

    if (m_socket == -1)
        throw std::runtime_error("Failed to create server socket");

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (::bind(m_socket, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        ::close(m_socket);
        throw std::runtime_error("Failed to bind server socket");
    }

    if (::listen(m_socket, SOMAXCONN) == -1) {
        ::close(m_socket);
        throw std::runtime_error("Failed to listen on server socket");
    }

    ::fcntl(m_socket, F_SETFL, O_NONBLOCK);
}

///////////////////////////////////////////////////////////////////////////////
Server::~Server()
{
    this->broadcast(Packet());

    for (const auto& client : m_clients)
        ::close(client.second->socket);
    ::close(m_socket);
}

///////////////////////////////////////////////////////////////////////////////
void Server::run(void)
{
    this->handleNewConnections();
    this->handleClientMessages();
}

///////////////////////////////////////////////////////////////////////////////
void Server::update(void)
{
    this->broadcast(Packet{Packet::PlayerMove{{42.f}, 5}});
}

///////////////////////////////////////////////////////////////////////////////
void Server::handleNewConnections(void)
{
    sockaddr_in addr;
    socklen_t len = sizeof(addr);
    Socket socket = ::accept(m_socket, (struct sockaddr*)&addr, &len);

    if (socket == -1)
        return;

    int id = m_nextId++;

    ::fcntl(socket, F_SETFL, O_NONBLOCK);

    {
        Packet::PlayerList playerList;
        playerList.count = m_clients.size();
        for (const auto& client : m_clients)
            playerList.players[client.first] = client.second->position;
        Packet packet(playerList);

        ::send(socket, packet.data(), packet.size(), 0);
    }

    m_clients[id] = std::make_unique<ClientInfo>(socket, Vec2f(0.f));

    this->broadcast(Packet{Packet::PlayerJoined{id}}, socket);
}

///////////////////////////////////////////////////////////////////////////////
void Server::handleClientMessages(void)
{
    for (auto it = m_clients.begin(); it != m_clients.end();) {
        Packet packet;
        int res = ::recv(
            it->second->socket,
            packet.data(),
            Packet::MAX_SIZE,
            0
        );

        if (res > 0) {
            packet.deserialize();

            if (const auto* move = packet.getIf<Packet::PlayerMove>()) {
                this->broadcast(
                    Packet(Packet::PlayerMove{move->position, it->first}),
                    m_clients[it->first]->socket
                );
            }

            ++it;
        } else if (
            res == 0 ||
            (res < 0 && errno != EWOULDBLOCK && errno != EAGAIN)
        ) {
            this->handleDisconnections(it++);
        } else {
            ++it;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
void Server::handleDisconnections(Map<int, UPtr<ClientInfo>>::iterator it)
{
    int id = it->first;

    ::close(it->second->socket);
    this->broadcast(Packet{Packet::PlayerLeft{id}}, it->second->socket);
    m_clients.erase(it);
}

///////////////////////////////////////////////////////////////////////////////
void Server::broadcast(const Packet& packet, Socket socket)
{
    for (const auto& client : m_clients) {
        if (client.second->socket != socket) {
            send(client.second->socket, packet.data(), packet.size(), 0);
        }
    }
}

} // namespace tkd
