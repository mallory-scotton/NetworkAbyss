///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Game/States/Menu.hpp>
#include <Engine/Resources/AssetsManager.hpp>
#include <Engine/Utils/Macros.hpp>

///////////////////////////////////////////////////////////////////////////////
// Namespace tkd::States
///////////////////////////////////////////////////////////////////////////////
namespace tkd::States
{

///////////////////////////////////////////////////////////////////////////////
Menu::Menu(void)
    : Base()
    , m_background(AssetsManager::getInstance()->getTexture("menu/background"))
    , m_logo(AssetsManager::getInstance()->getTexture("menu/logo_en"))
    , m_buffer(AssetsManager::getInstance()->getSound("musics/menu"))
    , m_music(*m_buffer)
    , m_sprite(*m_background)
{
    m_sprite.setOrigin(Vec2f(m_background->getSize()) / 2.f);
    m_music.setLooping(true);
    m_music.play();
}

///////////////////////////////////////////////////////////////////////////////
Menu::~Menu()
{
    auto assets = AssetsManager::getInstance();

    assets->unloadTexture("menu/background");
    assets->unloadTexture("menu/logo_en");
    assets->unloadSound("musics/menu");
}

///////////////////////////////////////////////////////////////////////////////
void Menu::update(float deltaT)
{
    UNUSED(deltaT);
    m_sprite.setPosition(Vec2f(m_renderer->getWindow().getSize()) / 2.f);
}

///////////////////////////////////////////////////////////////////////////////
void Menu::render(void)
{
    m_renderer->draw(m_sprite);
}

///////////////////////////////////////////////////////////////////////////////
void Menu::onStateChange(void)
{
    m_music.stop();
}

///////////////////////////////////////////////////////////////////////////////
void Menu::onStateFocus(void)
{
    m_music.play();
}

///////////////////////////////////////////////////////////////////////////////
void Menu::handleEvent(const sf::Event::KeyPressed& key)
{
    if (key.scancode == sf::Keyboard::Scancode::Escape)
        m_renderer->getWindow().close();
}

} // namespace tkd::States
