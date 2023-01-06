/**
 * @file interactServer.hpp
 * @brief interactServer
 */

#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include "client/SpaceShip.hpp"
#include "client/Ennemy.hpp"
#include "client/Bullets.hpp"
#include "Server.hpp"


/**
 * @class InteractServer
 * @brief class representing the InteractServer
 */
class InteractServer
{
public:
    /**
     * @brief InteractServer constructor
     * @param spaceShipSys, EnnemySys
     * @return InteractServer
     */
    InteractServer(std::shared_ptr<SpaceShipSys> spaceShipSys, std::shared_ptr<EnnemySys> EnnemySys);
    /**
     * @brief InteractServer destructor
     * @return ~InteractServer
     */
    ~InteractServer() {
        socketTcp.close();
        socketUdp.close();
    }
    /**
     * @brief Create server
     * @param container
     */
    void createServer(const std::shared_ptr<GameContainer>& container);
    /**
     * @brief Start receive information
     */
    void StartReceive();
    /**
     * @brief Server loop
     */
    void ServerLoop();
    /**
     * @brief Send server information
     */
    void sendServerInfos();
    /**
     * @brief test the communication between server and client
     * @param ec
     * @param bytes_transferred
     */
    void test(const boost::system::error_code &ec, std::size_t bytes_transferred);
    void Quit();
    /**
     * @brief get the server informations
     * @param ec
     * @param bytes_transferred
     */
    void getServerInfos(const boost::system::error_code &ec, std::size_t bytes_transferred);
    int life;

private:
    boost::array<char, 1024UL> _recv_buffer;
    std::shared_ptr<GameContainer> _container;
    std::shared_ptr<SpaceShipSys> _spaceShipSys;
    std::shared_ptr<EnnemySys> _ennemySys;
    boost::asio::io_service _io_service;
    boost::asio::ip::tcp::socket socketTcp;
    boost::asio::ip::udp::socket socketUdp;
    boost::asio::ip::tcp::endpoint _endpointTcp;
    boost::asio::ip::udp::endpoint _endpointUdp;
    boost::asio::ip::udp::endpoint receiver_endpoint_;
    boost::asio::ip::udp::endpoint sender_endpoint_;
    
};
