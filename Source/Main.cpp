///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine.hpp>
#include <Game.hpp>

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
    tkd::Engine engine(
        {800, 600},
        "NetworkAbyss",
        std::make_unique<tkd::States::Menu>()
    );

    engine.run();

    return (EXIT_SUCCESS);
}
