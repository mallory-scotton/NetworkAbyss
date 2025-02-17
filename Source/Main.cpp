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
    sf::RenderWindow* window = new sf::RenderWindow(
        sf::VideoMode({800, 600}), "NetworkAbyss", sf::Style::Close
    );

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->scancode == sf::Keyboard::Scancode::Escape)
                    window->close();
            }
        }

        window->display();

        window->clear();
    }

    delete window;

    return (EXIT_SUCCESS);
}
