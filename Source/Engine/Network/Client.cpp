///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Network/Client.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
Client::Client(void)
    : m_connected(false)
    , m_socket(INVALID_SOCKET_VALUE)
{
    if (Client::m_instance)
        delete Client::m_instance;
    Client::m_instance = this;
}

///////////////////////////////////////////////////////////////////////////////
Client::~Client()
{
    if (this->m_connected)
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
    if (this->m_connected)
        this->disconnect();

    this->m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->m_socket == INVALID_SOCKET_VALUE)
        return (false);

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = address.port;
    inet_pton(AF_INET, address.ip.c_str(), &addr.sin_addr);

    if (::connect(
            this->m_socket,
            (struct sockaddr*)&addr,
            sizeof(addr)
        ) == SOCKET_ERROR_VALUE) {
        closesocket(this->m_socket);
        return (false);
    }

#ifdef _WIN32
    u_long mode = 1;
    ioctlsocket(this->m_socket, FIONBIO, &mode);
#else
    fcntl(this->m_socket, F_SETFL, O_NONBLOCK);
#endif

    this->m_connected = true;
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
void Client::disconnect(void)
{
    if (this->m_connected) {
        this->m_connected = false;
        closesocket(this->m_socket);
        m_socket = INVALID_SOCKET_VALUE;
    }
}

///////////////////////////////////////////////////////////////////////////////
bool Client::send(const Packet& packet) const
{
    if (this->m_connected)
        return (false);
    ::send(this->m_socket, packet.data(), packet.size(), 0);
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
Optional<Packet> Client::pollPacket(void)
{
    if (!this->m_connected)
        return (std::nullopt);

    Packet packet;
    if (::recv(this->m_socket, packet.data(), packet.MAX_SIZE, 0) > 0)
        return (packet);

    return (std::nullopt);
}

} // namespace tkd
