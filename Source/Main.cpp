///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <Engine.hpp>
#include <Game.hpp>

#if defined(NEON_SERVER)

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <signal.h>

///////////////////////////////////////////////////////////////////////////////
tkd::Atomic<bool> running(true);

///////////////////////////////////////////////////////////////////////////////
void signalHandler(int signum)
{
    std::cout << "\nShutdown signal received (" << signum << ")." << std::endl;
    running = false;
}

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
    std::cout << "Starting game server..." << std::endl;

    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    tkd::Uint16 port = 55001;

    try {
        tkd::Server server(port);

        tkd::ServerDiscovery discovery(port);
        discovery.startBroadcasting();

        std::cout << "Server started on port " << port << std::endl;

        tkd::Thread sthread([&server](void){
            try {
                while (running) {
                    server.update();
                    std::this_thread::sleep_for(std::chrono::milliseconds(16));
                }
            } catch (const std::exception& e) {
                std::cerr << "Server thread error: " << e.what() << std::endl;
                running = false;
            }
        });

        while (running)
            server.run();
        std::cout << "Shutting down server..." << std::endl;
        if (sthread.joinable())
            sthread.join();
        std::cout << "Server shutdown complete." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

#elif defined(NEON_PACKER)

///////////////////////////////////////////////////////////////////////////////
// Dependencies
///////////////////////////////////////////////////////////////////////////////
#include <sstream>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
    tkd::AssetsPacker packer;
    std::string command;

    bool isTerminal = isatty(fileno(stdin));

    while (true) {
        if (isTerminal)
            std::cout << "packer> ";
        std::getline(std::cin, command);

        if (std::cin.eof())
            break;

        std::istringstream iss(command);
        std::string token;
        iss >> token;

        if (token == "pack" || token == "p") {
            std::string filename;
            if (iss >> filename)
                packer.pack(filename);
            else std::cout << "Usage: pack <filename>" << std::endl;
        } else if (token == "unpack" || token == "u") {
            std::string filename;
            if (iss >> filename)
                try { packer.unpack(filename); }
                catch (const std::exception& e) {}
            else std::cout << "Usage: unpack <filename>" << std::endl;
        } else if (token == "add" || token == "a") {
            std::string filename;
            std::string key;
            if (iss >> filename >> key) {
                try {
                    packer.addAsset(key, filename);
                } catch (const std::exception& error) {
                    std::cout << "Error: " << error.what() << std::endl;
                }
            } else std::cout << "Usage: add <filename> <key>" << std::endl;
        } else if (token == "display" || token == "d") {
            std::cout << packer;
        } else if (token == "clear") {
            packer.clear();
        }  else if (token == "quit" || token == "q") {
            break;
        } else {
            std::cout << "Unknown command: " << token << std::endl;
        }
    }

    return (EXIT_SUCCESS);
}

#else

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
    tkd::Engine engine(
        {800, 600},
        "NetworkAbyss",
        std::make_unique<tkd::States::Discovery>()
    );

    engine.run();

    return (EXIT_SUCCESS);
}

#endif
