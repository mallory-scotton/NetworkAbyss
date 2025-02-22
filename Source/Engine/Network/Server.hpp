///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Network/Packet.hpp>
#include <Engine/Utils/Singleton.hpp>
#include <Engine/Utils/Types.hpp>
#include <Engine/Utils/Vec2.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class Server : Singleton<Server>
{
private:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    struct ClientInfo
    {
        Socket socket;                      //<!
        Vec2f position;                     //<!
    };

private:
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    Socket m_socket;                        //<!
    Map<int, UPtr<ClientInfo>> m_clients;   //<!
    int m_nextId;                           //<!

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param port
    ///
    ///////////////////////////////////////////////////////////////////////////
    Server(Uint16 port = 55001);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    ~Server();

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    void run(void);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    void update(void);

private:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    void handleNewConnections(void);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    void handleClientMessages(void);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param it
    ///
    ///////////////////////////////////////////////////////////////////////////
    void handleDisconnections(Map<int, UPtr<ClientInfo>>::iterator it);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param packet
    /// \param socket
    ///
    ///////////////////////////////////////////////////////////////////////////
    void broadcast(const Packet& packet, Socket socket = -1);
};

} // namespace tkd
