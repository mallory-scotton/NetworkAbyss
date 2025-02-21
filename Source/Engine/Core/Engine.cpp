///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Core/Engine.hpp>
#include <Engine/Resources/AssetsManager.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
Engine::Engine(
    const Vec2u& dimension,
    const String& title,
    StateManager::State state
)
    : m_renderer(dimension, title)
    , m_stateManager(&m_renderer.getWindow())
{
    m_stateManager.push(std::move(state));
}

///////////////////////////////////////////////////////////////////////////////
void Engine::run(void)
{
    while (m_renderer.getWindow().isOpen()) {
        float deltaT = m_clock.restart().asSeconds();

        m_stateManager.handleEvents();
        m_stateManager.handlePackets();

        m_stateManager.update(deltaT);

        m_renderer.clear();
        m_stateManager.render();
        m_renderer.display();

        if (m_stateManager.empty())
            m_renderer.getWindow().close();
    }
}

} // namespace tkd
