/**
 * @file Ennemy.hpp
 * @brief Ennemy
 */
#pragma once
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <map>
#include <cmath>
#include "Coordinator.hpp"
#include "utils/Vector.hpp"



/**
 * @class EnnemyComp
 * @brief Initialise Ennemies pos
 */
class enemyComp {
public:
    explicit enemyComp(Vector2f pos, unsigned int id, unsigned int life, unsigned int type);
    Vector2f pos;
    Vector2f BasePos;
    unsigned int life;
    unsigned int id;
    unsigned int type;
};

/**
 * @class EnemySys
 * @brief Initialise Ennemies mmoves
 */
class EnemySys : public ecs::System {
public:
    void move(long timeMs);
    int getNewId(unsigned int type);
    void sendPos(boost::asio::basic_datagram_socket<boost::asio::ip::udp> &socket, const boost::asio::ip::basic_endpoint<boost::asio::ip::udp> &endpoint);
    bool enemyTouched(int id);
    void enemyShoot(boost::asio::basic_datagram_socket<boost::asio::ip::udp> &socket, const boost::asio::ip::basic_endpoint<boost::asio::ip::udp> &endpoint);
};