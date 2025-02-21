///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Game/States/Discovery.hpp>
#include <Game/States/Play.hpp>
#include <Engine/Utils/Macros.hpp>
#include <Engine/Network/Client.hpp>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd::States
///////////////////////////////////////////////////////////////////////////////
namespace tkd::States
{

///////////////////////////////////////////////////////////////////////////////
Discovery::Discovery(void)
    : Base()
{
    m_discovery.startListening([this](const Address& address) {
        if (std::find(
                m_addresses.begin(),
                m_addresses.end(),
                address
            ) == m_addresses.end()) {
            m_addresses.push_back(address);
        }
    });

    m_shape.setSize({200.f, 50.f});
    m_shape.setOrigin({100.f, 25.f});
    m_shape.setFillColor(sf::Color::Green);
}

///////////////////////////////////////////////////////////////////////////////
Discovery::~Discovery()
{
    m_discovery.stop();
}

///////////////////////////////////////////////////////////////////////////////
void Discovery::update(float deltaT)
{
    UNUSED(deltaT);
}

///////////////////////////////////////////////////////////////////////////////
void Discovery::render(void)
{
    for (Uint64 i = 0; i < m_addresses.size(); i++) {
        m_shape.setPosition({400.f, 50.f + 75.f * (float)i});
        m_window->draw(m_shape);
    }
}

///////////////////////////////////////////////////////////////////////////////
void Discovery::handleEvent(const sf::Event::MouseButtonPressed& mouse)
{
    Client* client = Client::getInstance();

    for (Uint64 i = 0; i < m_addresses.size(); i++) {
        m_shape.setPosition({400.f, 50.f + 75.f * (float)i});

        if (
            m_shape.getGlobalBounds().contains(Vec2f(mouse.position)) &&
            client->connect(m_addresses[i])
        ) {
            m_stateManager->change(std::make_unique<States::Play>());
            break;
        }
    }
}

} // namespace tkd::States
