/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Protocol
*/

#pragma once
#include "Coordinator.hpp"
#include "ecs/Enemy.hpp"

bool isClient(boost::asio::ip::udp::endpoint remote_endpoint, std::vector<boost::asio::ip::udp::endpoint> clients);
void sendCodeToAllClients(boost::asio::ip::udp::endpoint remote_endpoint, std::vector<boost::asio::ip::udp::endpoint> clients, boost::asio::ip::udp::socket socket, std::string msg);