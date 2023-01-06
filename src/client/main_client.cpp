#include <iostream>
#include "client/GameGraphic.hpp"
#include "client/GameContainer.hpp"
#include "Coordinator.hpp"
#include "client/Button.hpp"
#include <boost/asio.hpp>
ecs::Coordinator gCoordinator;

int main(int argc, char **argv)
{
    if (argc < 3 || (argv[1][0] == '-' && argv[1][1] == 'h')) {
        std::cerr << "Usage: ./r-type_client ip port" << std::endl;
        return 84;
    }
    try {
        gCoordinator.Init();
        GameGraphic game;
        game._container->argv = argv;
        game.loop();
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    gCoordinator.~Coordinator();
    return 0;
}
