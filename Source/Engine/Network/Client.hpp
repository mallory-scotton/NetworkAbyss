///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Network/Network.hpp>
#include <Engine/Network/Packet.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class Client
{
private:
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    static Client* m_instance;  //<!
    bool m_connected;           //<!
    Socket m_socket;            //<!

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    Client(void);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    ~Client();

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    Client& operator<<(const Packet& packet);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    bool operator>>(Packet& packet);

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    static Client* getInstance(void);

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    bool connect(const Address& address);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    void disconnect(void);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param packet
    ///
    ///////////////////////////////////////////////////////////////////////////
    bool send(const Packet& packet) const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param packet
    ///
    /// \return
    ///
    ///////////////////////////////////////////////////////////////////////////
    Optional<Packet> pollPacket(void);
};

} // namespace tkd
