///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine.hpp>
#include <Game.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
    tkd::AssetsPacker packer;
    sf::RenderWindow* window = new sf::RenderWindow(
        sf::VideoMode({800, 600}), "NetworkAbyss", sf::Style::Close
    );

    tkd::States::Base base;
    base.m_window = window;

    packer.unpack("assets.pak");

    tkd::SPtr<sf::Texture> texture = packer.getTexture("placeholder").value_or(nullptr);

    sf::Sprite sprite(*texture);

    sprite.setPosition({400, 300});
    sprite.setOrigin({(*texture).getSize().x / 2.f, (*texture).getSize().y / 2.f});
    sprite.setScale({1.0f, 1.0f});
    sprite.setTextureRect({{0, 0}, {600, 400}});

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            tkd::OverloadSet set{[&base](const auto& event) { base.handleEvent(event);}};
            event->visit(set);
        }

        window->clear();

        window->draw(sprite);

        window->display();
    }

    delete window;

    return (EXIT_SUCCESS);
}
