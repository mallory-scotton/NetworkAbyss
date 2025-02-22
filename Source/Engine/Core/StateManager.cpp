///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Core/StateManager.hpp>
#include <Engine/Network/Client.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
StateManager::StateManager(void)
    : m_renderer(Renderer::getInstance())
{}

///////////////////////////////////////////////////////////////////////////////
void StateManager::push(State state)
{
    if (!m_states.empty())
        m_states.top()->onStateChange();
    m_states.push(std::move(state));
}

///////////////////////////////////////////////////////////////////////////////
void StateManager::pop(void)
{
    if (!m_states.empty())
        m_states.pop();
    if (!m_states.empty())
        m_states.top()->onStateFocus();
}

///////////////////////////////////////////////////////////////////////////////
void StateManager::change(State state)
{
    this->pop();
    this->push(std::move(state));
}

///////////////////////////////////////////////////////////////////////////////
void StateManager::handleEvents(void)
{
    if (m_states.empty())
        return;

    OverloadSet set{[this](const auto& event){
        m_states.top()->handleEvent(event);
    }};

    while (const auto event = m_renderer->getWindow().pollEvent())
        event->visit(set);
}

///////////////////////////////////////////////////////////////////////////////
void StateManager::handlePackets(void)
{
    if (m_states.empty())
        return;

    Client* client = Client::getInstance();

    OverloadSet set{[this](const auto& packet){
        m_states.top()->handlePacket(packet);
    }};

    while (const Optional<Packet> packet = client->pollPacket())
        packet->visit(set);
}

///////////////////////////////////////////////////////////////////////////////
void StateManager::update(float deltaT)
{
    if (m_states.empty())
        return;
    m_states.top()->update(deltaT);
}

///////////////////////////////////////////////////////////////////////////////
void StateManager::render(void)
{
    if (m_states.empty())
        return;
    m_states.top()->render();
}

///////////////////////////////////////////////////////////////////////////////
bool StateManager::empty(void) const
{
    return (m_states.empty());
}

} // namespace tkd
