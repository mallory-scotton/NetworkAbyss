///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Network/Client.hpp>
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
Client::Client(void)
    : m_connected(false)
    , m_socket(-1)
{
    if (Client::m_instance)
        delete Client::m_instance;
    Client::m_instance = this;
}

///////////////////////////////////////////////////////////////////////////////
Client::~Client()
{
    if (m_connected)
        this->disconnect();
}

///////////////////////////////////////////////////////////////////////////////
Client& Client::operator<<(const Packet& packet)
{
    this->send(packet);
    return (*this);
}

///////////////////////////////////////////////////////////////////////////////
bool Client::operator>>(Packet& packet)
{
    Optional<Packet> rpacket = this->pollPacket();

    if (rpacket) {
        packet = *rpacket;
        return (true);
    }
    return (false);
}

///////////////////////////////////////////////////////////////////////////////
Client* Client::getInstance(void)
{
    if (!Client::m_instance)
        Client::m_instance = new Client();
    return (Client::m_instance);
}

///////////////////////////////////////////////////////////////////////////////
bool Client::connect(const Address& address)
{
    if (m_connected)
        this->disconnect();

    m_socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == -1)
        return (false);

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = address.port;
    ::inet_pton(AF_INET, address.ip.c_str(), &addr.sin_addr);

    if (::connect(m_socket, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        ::close(m_socket);
        return (false);
    }

    ::fcntl(m_socket, F_SETFL, O_NONBLOCK);

    m_connected = true;
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
void Client::disconnect(void)
{
    if (m_connected) {
        m_connected = false;
        ::close(m_socket);
        m_socket = -1;
    }
}

///////////////////////////////////////////////////////////////////////////////
bool Client::send(const Packet& packet) const
{
    if (m_connected)
        return (false);
    ::send(m_socket, packet.data(), packet.size(), 0);
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
Optional<Packet> Client::pollPacket(void)
{
    if (!m_connected)
        return (std::nullopt);

    Packet packet;
    if (::recv(m_socket, packet.data(), packet.MAX_SIZE, 0) > 0)
        return (packet);

    return (std::nullopt);
}

} // namespace tkd
