///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Network/ServerDiscovery.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
const Uint16 ServerDiscovery::DISCOVERY_PORT = 55000;

///////////////////////////////////////////////////////////////////////////////
const char* ServerDiscovery::DISCOVERY_MESSAGE = "TKD_NETWORKABYSS_SERV";

///////////////////////////////////////////////////////////////////////////////
ServerDiscovery::ServerDiscovery(Uint16 port)
    : m_running(false)
    , m_port(port)
    , m_socket(-1)
{};

///////////////////////////////////////////////////////////////////////////////
ServerDiscovery::~ServerDiscovery()
{
    this->stop();
}

///////////////////////////////////////////////////////////////////////////////
void ServerDiscovery::startBroadcasting(void)
{
    if (m_running)
        return;

    m_running = true;

    m_thread = Thread([this](void) {
        m_socket = ::socket(AF_INET, SOCK_DGRAM, 0);

        if (m_socket < 0) {
            std::cerr << "Failed to create discovery socket" << std::endl;
            return;
        }

        int broadcast = 1;
        ::setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST,
            (char*)&broadcast, sizeof(broadcast));

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(DISCOVERY_PORT);
        addr.sin_addr.s_addr = INADDR_BROADCAST;

        String messsage = DISCOVERY_MESSAGE;
        messsage += std::to_string(m_port);

        while (m_running) {
            ::sendto(m_socket, messsage.c_str(), messsage.length(), 0,
                (struct sockaddr*)&addr, sizeof(addr));
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        ::close(m_socket);
        m_socket = -1;
    });
}

///////////////////////////////////////////////////////////////////////////////
void ServerDiscovery::startListening(ServerDiscovery::Callback callback)
{
    if (m_running)
        return;

    m_running = true;
    m_callback = callback;

    m_thread = Thread([this](void) {
        m_socket = ::socket(AF_INET, SOCK_DGRAM, 0);

        if (m_socket < 0) {
            std::cerr << "Failed to create discovery socket" << std::endl;
            return;
        }

        int flags = ::fcntl(m_socket, F_GETFL, 0);
        ::fcntl(m_socket, F_SETFL, flags | O_NONBLOCK);

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(DISCOVERY_PORT);
        addr.sin_addr.s_addr = INADDR_ANY;

        if (::bind(m_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            std::cerr << "Failed to bind discovery socket" << std::endl;
            ::close(m_socket);
            m_socket = -1;
            return;
        }

        while (m_running) {
            char buffer[256];
            sockaddr_in saddr;
            socklen_t slen = sizeof(saddr);

            int received = ::recvfrom(m_socket, buffer, sizeof(buffer), 0,
                (struct sockaddr*)&saddr, &slen);

            if (received > 0) {
                buffer[received] = '\0';

                char msg[256];
                int port;

                if (
                    ::sscanf(buffer, "%[^:]:%d", msg, &port) == 2 &&
                    ::strcmp(msg, DISCOVERY_MESSAGE) == 0
                ) {
                    char ip[INET_ADDRSTRLEN];
                    ::inet_ntop(AF_INET, &(saddr.sin_addr), ip,
                        INET_ADDRSTRLEN);
                    if (m_callback)
                        m_callback(Address{ip, (Uint16)port});
                }
            }
        }

        ::close(m_socket);
        m_socket = -1;
    });
}

///////////////////////////////////////////////////////////////////////////////
void ServerDiscovery::stop(void)
{
    if (!m_running)
        return;
    m_running = false;
    if (m_socket != -1)
        ::shutdown(m_socket, SHUT_RDWR);
    if (m_thread.joinable())
        m_thread.join();
}

} // namespace tkd
