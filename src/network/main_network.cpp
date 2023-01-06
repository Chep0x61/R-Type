#include <iostream>
#include "Server.hpp"
#include "Coordinator.hpp"
#include "client/Button.hpp"
#include "ecs/Enemy.hpp"
#include "utils/Vector.hpp"

ecs::Coordinator gCoordinator;

void callable() {
    std::cout << "Hello from thread" << std::endl;
}

int main(int argc, char** argv)
{
    gCoordinator.Init();
    try {
        unsigned int port = 13;
        if (argc >= 2)
            port = std::stoi(argv[1]);
        else
            std::cout << "no port specified: default is " << port << std::endl;
        Server server(port);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
