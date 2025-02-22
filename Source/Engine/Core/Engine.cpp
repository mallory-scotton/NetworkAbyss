///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine/Core/Engine.hpp>
#include <Engine/Resources/AssetsManager.hpp>
#include <Game/States/Menu.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd
///////////////////////////////////////////////////////////////////////////////
namespace tkd
{

///////////////////////////////////////////////////////////////////////////////
Engine::Engine(void)
    : m_renderer(Renderer::getInstance())
    , m_stateManager(StateManager::getInstance())
{
    m_stateManager->push(std::make_unique<States::Menu>());
}

///////////////////////////////////////////////////////////////////////////////
void Engine::run(void)
{
    while (m_renderer->getWindow().isOpen()) {
        float deltaT = m_clock.restart().asSeconds();

        m_stateManager->handleEvents();
        m_stateManager->handlePackets();

        m_stateManager->update(deltaT);

        m_renderer->clear();
        m_stateManager->render();
        m_renderer->display();

        if (m_stateManager->empty())
            m_renderer->getWindow().close();
    }
}

} // namespace tkd
