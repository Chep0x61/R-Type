/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Network
*/

/**
 * @file Network.hpp
 * @brief UDP & TCP Protocol with Boost::Asio
 */

#pragma once

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <boost/enable_shared_from_this.hpp>
#include <thread>
#include <chrono>
#include <memory>
#include "ecs/Enemy.hpp"

/**
 * @class TCP_Connection
 * @brief class representing the TCP Connection
 */
class TCP_Connection : public boost::enable_shared_from_this<TCP_Connection> {
public:
    /**
     * @brief Create TCP Connection
     * @param boost::asio::io_context &
     * @return explicit TCP_Connection
     */
    explicit TCP_Connection(boost::asio::io_context &ioc);
    typedef boost::shared_ptr<TCP_Connection> pointer;

    /**
     * @brief Create TCP Socket
     * @return boost::asio::ip::tcp::socket&
     */
    boost::asio::ip::tcp::socket& socket();
    /**
     * @brief Runs TCP Connection
     */
    void start();
    /**
     * @brief Handle Write
     * @param const boost::system::error_code &
     */
    void handleWrite(const boost::system::error_code &);
private:

    boost::asio::ip::tcp::socket _socket;
    std::string _message;
};

/**
 * @class TCP_Server
 * @brief class representing the TCP Server
 */
class TCP_Server {
public:
    /**
     * @brief Create TCP Server
     * @param boost::asio::io_context&
     * @return explicit UDP_Server
     */
    explicit TCP_Server(boost::asio::io_context&);
    /**
     * @brief Get Client Connection
     * @return std::vector<TCP_Connection::pointer>
     */
    std::vector<TCP_Connection::pointer> getConnexions() const;
private:
    void startAccept();
    void handleAccept(const TCP_Connection::pointer&, const boost::system::error_code&);

    boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::io_context &_io_context;
    std::vector<TCP_Connection::pointer> _connections;
};

/**
 * @class UDP_Server
 * @brief class representing the UDP_Server
 */
class UDP_Server : public boost::enable_shared_from_this<UDP_Server> {
public:
    /**
     * @brief Destructor of the Network
     * @param boost::asio::io_context&
     * @return explicit UDP_Server
     */
    explicit UDP_Server(boost::asio::io_context&, unsigned int port);
    std::vector<boost::asio::ip::udp::endpoint> _clients;
    boost::asio::ip::udp::socket _socket;
    std::shared_ptr<EnemySys> enemySys;
private:
    void startReceive();
    void handleReceive(const boost::system::error_code&, std::size_t);
    void handleSend(const boost::shared_ptr<std::string>, const boost::system::error_code&, std::size_t);
    int getClientId(boost::asio::ip::udp::endpoint endpoint);

    boost::asio::ip::udp::endpoint _remote_endpoint;
    boost::array<char, 1024> _recv_buffer{};

};
/**
 * @class Network
 * @brief class representing UDP & TCP Protocol Network
 */
class Network {
public:
    /**
     * @brief Constructor of the Network
     */
    Network(unsigned int port);
    /**
     * @brief Destructor of the Network
     */
    ~Network() = default;

    void setUpEcs();
    void gameLoop();
    /**
     * @brief Callable
     */
    void callable();
private:
    boost::asio::io_context _io_context_server;
    TCP_Server _tcp_server;
    UDP_Server _udp_server;
};