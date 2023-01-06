#include <boost/asio.hpp>
#include "Network.hpp"

bool isClient(boost::asio::ip::udp::endpoint remote_endpoint, std::vector<boost::asio::ip::udp::endpoint> clients)
{
    if (clients.size() == 0)
        return false;
    for (auto it = clients.begin(); it != clients.end(); it++)
        if (*it == remote_endpoint)
            return true;
    return false;
}

void sendCodeToAllClients(boost::asio::ip::udp::endpoint remote_endpoint, std::vector<boost::asio::ip::udp::endpoint> clients, boost::asio::ip::udp::socket socket, std::string msg)
{
    for (auto it = clients.begin(); it != clients.end(); it++)
        if (*it == remote_endpoint)
            socket.send_to(boost::asio::buffer(msg), *it);
}

void UDP_Server::handleReceive(const boost::system::error_code &ec, std::size_t bytes_transferred)
{
    int count = 0;
    static int killed = 0;
    if (!ec)
    {
        if (!isClient(_remote_endpoint, _clients))
            _clients.push_back(_remote_endpoint);
        std::string code = std::string(_recv_buffer.begin(), _recv_buffer.begin() + bytes_transferred);
        if (!code.rfind("060", 0))
            for (auto it = _clients.begin(); it != _clients.end(); it++)
                if (*it == _remote_endpoint) {
                    _socket.send_to(boost::asio::buffer("160" + std::to_string(getClientId(_remote_endpoint))), *it);
                    std::cout << "New Client Connected, ID:" << std::to_string(getClientId(_remote_endpoint)) << std::endl;
                }
        if (!code.rfind("011", 0))
        {
            int x = std::stoi(code.substr(3, code.find(";") - 3));
            int y = std::stoi(code.substr(code.find(";") + 1));
            for (auto it = _clients.begin(); it != _clients.end(); it++)
                if (*it != _remote_endpoint)
                    _socket.send_to(boost::asio::buffer("111" + std::to_string(getClientId(_remote_endpoint)) + std::to_string(x) + ";" + std::to_string(y)), *it);
        }
        if (!code.rfind("012", 0)) {
            for (auto & _client : _clients)
                if (_client != _remote_endpoint)
                    _socket.send_to(boost::asio::buffer("112" + std::to_string(getClientId(_remote_endpoint))), _client);
        }
        if (!code.rfind("013", 0)) {
            for (auto & _client : _clients)
                if (_client != _remote_endpoint)
                    _socket.send_to(boost::asio::buffer("113" + std::to_string(getClientId(_remote_endpoint))), _client);
        }
        if (!code.rfind("024", 0)) {
            if (enemySys != nullptr) {
                if (enemySys->enemyTouched(code[3] - 48)) {
                    killed++;
                    if (killed && killed % 4 == 0 && killed <= 16)
                        gCoordinator.AddComponent < std::shared_ptr < enemyComp
                                >> (gCoordinator.CreateEntity(), std::make_shared<enemyComp>(Vector2f(950, 400),
                                                                                             enemySys->getNewId(0), 10,
                                                                                             1));
                }
            }
        }
    }
    startReceive();
}