/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** interactServer
*/

#include "client/interactServer.hpp"

InteractServer::InteractServer(std::shared_ptr<SpaceShipSys> spaceShipSys, std::shared_ptr<EnnemySys> EnnemySys) : _spaceShipSys(spaceShipSys), _ennemySys(EnnemySys), socketUdp(_io_service), socketTcp(_io_service)
{
}

void InteractServer::test(const boost::system::error_code &ec, std::size_t bytes_transferred)
{
    // std::cout << bytes_transferred << std::endl;
    // std::cout << std::string(_recv_buffer.begin(), _recv_buffer.begin() + bytes_transferred) << std::endl;
}

void InteractServer::createServer(const std::shared_ptr<GameContainer>& container)
{
    _container = container;
    // _endpointTcp = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(container->argv[1]), std::stoi(container->argv[2]));
    _endpointUdp = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(container->argv[1]), std::stoi(container->argv[2]));
    // socketTcp.connect(_endpointTcp);
    socketUdp.open(boost::asio::ip::udp::v4());
    boost::asio::ip::udp::resolver udp_resolver(_io_service);
    boost::asio::ip::udp::resolver::query udp_query(boost::asio::ip::udp::v4(), container->argv[1], container->argv[2]);
    receiver_endpoint_ = *udp_resolver.resolve(udp_query);
    socketTcp.async_read_some( boost::asio::buffer(_recv_buffer, 1024), boost::bind(&InteractServer::test, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    socketUdp.connect(_endpointUdp);
    socketUdp.send(boost::asio::buffer(std::string("060")));

}

void InteractServer::ServerLoop()
{
    try {
        StartReceive();
        std::thread thr{[this]{ this->_io_service.run();}};
        while (_container->window->isOpen()) {
            sendServerInfos();
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
        this->_io_service.stop();
        thr.join();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void InteractServer::StartReceive()
{
    if (!_container->window->isOpen())
        return;
    socketUdp.async_receive(boost::asio::buffer(_recv_buffer),
                                 boost::bind(&InteractServer::getServerInfos,
                                             this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
}

void InteractServer::sendServerInfos()
{
    std::shared_ptr<SpaceShipComp> player = _spaceShipSys->getPlayer();
    std::shared_ptr<sf::Sprite> playerSprite = _spaceShipSys->getPlayerSprite();
    if (player == nullptr || playerSprite == nullptr) return;

    sf::Vector2f posPlayer = playerSprite->getPosition();
    socketUdp.send(boost::asio::buffer(std::string("011") + std::to_string((int)posPlayer.x) + ";"+ std::to_string((int)posPlayer.y)));

     if (life == 0) {
         socketUdp.send(boost::asio::buffer("013"));
         life = -1;
         _spaceShipSys->destroySpaceShip(_spaceShipSys->getPlayer()->nbPlayer);
     }
    
    if (player->isShooting) {
        socketUdp.send(boost::asio::buffer(std::string("012")));// 012 = le player à shoot
        player->isShooting = false;
    }

    for (unsigned int touchedId : _ennemySys->enemiesTouched) {
        socketUdp.send(boost::asio::buffer(std::string("024") + std::to_string(touchedId)));
    }
    _ennemySys->enemiesTouched.clear();


    //if (isEnnemyTouched == true)
        // 024N = ennemi N a été touché
    
    //if (isObstacleTouched == true)
        // 034N = obstacle N a été touché
}

void InteractServer::getServerInfos(const boost::system::error_code &ec, std::size_t bytes_transferred)
{
    if (ec) {
        std::cout << "error:" << ec << std::endl;
        StartReceive();
        return;
    }
    std::string code = std::string(_recv_buffer.begin(), _recv_buffer.begin() + bytes_transferred);
    if (!code.rfind("160", 0)) {
        createSpaceShip("assets/character/SpaceShips.gif", {0, 0}, std::stoi(code.substr(3,1)), true);
    }

    if (!code.rfind("111", 0)) {
        int id = std::stoi(code.substr(3,1));
        std::shared_ptr<SpaceShipComp> player = _spaceShipSys->getPlayerById(id);
        if (player == nullptr) {
            createSpaceShip("assets/character/SpaceShips.gif", {0, 0}, id, false);
            player = _spaceShipSys->getPlayerById(id);
        }
        int x = std::stoi(code.substr(4, code.find(";") - 4));
        int y = std::stoi(code.substr(code.find(";") + 1));
        _spaceShipSys->setPosition(id, {static_cast<float>(x), static_cast<float>(y)});
    }

    if (!code.rfind("112", 0)) {
        int id = code[3] - 48;
        std::shared_ptr<SpaceShipComp> player = _spaceShipSys->getPlayerById(id);
        if (player == nullptr) {
            createSpaceShip("assets/character/SpaceShips.gif", {0, 0}, id, false);
            player = _spaceShipSys->getPlayerById(id);
        }
        player->shoot(*_spaceShipSys->getSpriteByid(id));
    }

    if (!code.rfind("113", 0)) {
        int id = code[3] - 48;
        _spaceShipSys->destroySpaceShip(id);
    }
    if (!code.rfind("121", 0)) {
        int id = code[3] - 48;
        int type = code[4] - 48;
        int x = std::stoi(code.substr(5, code.find(";") - 5));
        int y = std::stoi(code.substr(code.find(";") + 1));
        std::shared_ptr<EnnemyComp> enemy = _ennemySys->getEnnemyById(id);
        if (enemy == nullptr) {
            if (type == 0)
                gCoordinator.AddComponent(gCoordinator.CreateEntity(), std::make_shared<EnnemyComp>("assets/character/ennemy.png", (ENNEMY_TYPE)type, sf::Vector2f((float)x, (float)y), id));
            if (type == 1)
                gCoordinator.AddComponent(gCoordinator.CreateEntity(), std::make_shared<EnnemyComp>("assets/character/boss.png", (ENNEMY_TYPE)type, sf::Vector2f((float)x, (float)y), id));
        } else
            enemy->sprite.setPosition({(float)x, (float)y});
    }

     if (!code.rfind("122", 0)) {
         int id = code[3] - 48;
         std::shared_ptr<EnnemyComp> enemy = _ennemySys->getEnnemyById(id);
         if (enemy != nullptr)
            createBullet( {enemy->sprite.getPosition().x - 48, enemy->sprite.getPosition().y + enemy->sprite.getGlobalBounds().height / 2}, LEFT, 2, true);
     }

    // if (code == "123N")
        // ennemi N est mort

    // if (code == "125N")
        // ennemi N a drop un bonus

    // if (code == "130NT")
        // obstacle N de type T a été créé

    // if (code == "131NX;Y")
        //  = obstacle N se trouve aux pos X,Y

    // if (code == "133N")
        // obstacle N est mort

    // if (code == "135N")
        // obstacle N a drop un bonus

    StartReceive();
}

void InteractServer::Quit() {
    socketUdp.send(boost::asio::buffer("013"));
}
