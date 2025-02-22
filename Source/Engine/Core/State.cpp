///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Core/State.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd::States
///////////////////////////////////////////////////////////////////////////////
namespace tkd::States
{

///////////////////////////////////////////////////////////////////////////////
Base::Base(void)
    : m_renderer(Renderer::getInstance())
    , m_stateManager(StateManager::getInstance())
{}

///////////////////////////////////////////////////////////////////////////////
void Base::handleEvent(const sf::Event::Closed&)
{
    m_renderer->close();
}

} // namespace tkd::States
