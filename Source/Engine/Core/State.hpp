///////////////////////////////////////////////////////////////////////////////
// Header guard
///////////////////////////////////////////////////////////////////////////////
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Utils/Types.hpp>
#include <Engine/Core/StateManager.hpp>
#include <Engine/Network/Packet.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
// Pre-definition of the state manager class
///////////////////////////////////////////////////////////////////////////////
class StateManager;

} // namespace tkd


///////////////////////////////////////////////////////////////////////////////
// Namespace tkd::States
///////////////////////////////////////////////////////////////////////////////
namespace tkd::States
{

///////////////////////////////////////////////////////////////////////////////
/// \brief
///
///////////////////////////////////////////////////////////////////////////////
class Base
{
public:
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    friend class tkd::StateManager;

protected:
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    StateManager* m_stateManager;       //<!
    sf::RenderWindow* m_window;         //<!

public:
    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    virtual void init(void) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param deltaT
    ///
    ///////////////////////////////////////////////////////////////////////////
    virtual void update(float deltaT) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    ///////////////////////////////////////////////////////////////////////////
    virtual void render(void) = 0;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param
    ///
    ///////////////////////////////////////////////////////////////////////////
    void handlePacket(const Packet::Connect&) {};
    void handlePacket(const Packet::Disconnect&) {};
    void handlePacket(const Packet::PlayerMove&) {};
    void handlePacket(const Packet::PlayerList&) {};
    void handlePacket(const Packet::PlayerJoined&) {};
    void handlePacket(const Packet::PlayerLeft&) {};
    template <typename T> void handlePacket(const T&) {};

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param
    ///
    ///////////////////////////////////////////////////////////////////////////
    void handleEvent(const sf::Event::Closed&);

    ///////////////////////////////////////////////////////////////////////////
    /// \brief
    ///
    /// \param
    ///
    ///////////////////////////////////////////////////////////////////////////
    virtual void handleEvent(const sf::Event::Resized&) {};
    virtual void handleEvent(const sf::Event::FocusLost&) {};
    virtual void handleEvent(const sf::Event::FocusGained&) {};
    virtual void handleEvent(const sf::Event::TextEntered&) {};
    virtual void handleEvent(const sf::Event::KeyPressed&) {};
    virtual void handleEvent(const sf::Event::KeyReleased&) {};
    virtual void handleEvent(const sf::Event::MouseWheelScrolled&) {};
    virtual void handleEvent(const sf::Event::MouseButtonPressed&) {};
    virtual void handleEvent(const sf::Event::MouseButtonReleased&) {};
    virtual void handleEvent(const sf::Event::MouseMoved&) {};
    virtual void handleEvent(const sf::Event::MouseMovedRaw&) {};
    virtual void handleEvent(const sf::Event::MouseEntered&) {};
    virtual void handleEvent(const sf::Event::MouseLeft&) {};
    virtual void handleEvent(const sf::Event::JoystickButtonPressed&) {};
    virtual void handleEvent(const sf::Event::JoystickButtonReleased&) {};
    virtual void handleEvent(const sf::Event::JoystickMoved&) {};
    virtual void handleEvent(const sf::Event::JoystickConnected&) {};
    virtual void handleEvent(const sf::Event::JoystickDisconnected&) {};
    virtual void handleEvent(const sf::Event::TouchBegan&) {};
    virtual void handleEvent(const sf::Event::TouchMoved&) {};
    virtual void handleEvent(const sf::Event::TouchEnded&) {};
    virtual void handleEvent(const sf::Event::SensorChanged&) {};
    template <typename T> void handleEvent(const T&) {};
};

} // namespace tkd::States
