#include <chrono>
#include <thread>
#include "Network.hpp"
#include "Protocol.hpp"

TCP_Server::TCP_Server(boost::asio::io_context &ioc) : _acceptor(ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 13)), _io_context(ioc)
{
    startAccept();
}

void TCP_Server::startAccept()
{
    TCP_Connection::pointer newConnection = boost::shared_ptr<TCP_Connection>(new TCP_Connection(_io_context));
    _acceptor.async_accept(newConnection->socket(),
                           boost::bind(&TCP_Server::handleAccept,
                                       this,
                                       newConnection,
                                       boost::asio::placeholders::error));
}

void TCP_Server::handleAccept(const TCP_Connection::pointer &newConnection, const boost::system::error_code &ec)
{
    if (!ec)
    {
        newConnection->start();
    }
    startAccept();
    _connections.push_back(newConnection);
}

UDP_Server::UDP_Server(boost::asio::io_context &ioc, unsigned int port) : _socket(ioc, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
    std::cout << "listening on port " << port << std::endl;
    startReceive();
}

std::vector<TCP_Connection::pointer> TCP_Server::getConnexions() const
{
    return _connections;
}

void Network::callable()
{
    _io_context_server.run();
}

void Network::setUpEcs()
{
    _udp_server.enemySys = gCoordinator.RegisterSystem<EnemySys>();
    gCoordinator.RegisterComponent<std::shared_ptr<enemyComp>>();
    Signature enemySignature;
    enemySignature.set(gCoordinator.GetComponentType<std::shared_ptr<enemyComp>>());
    gCoordinator.setSystemSignature<EnemySys>(enemySignature);
    srand((unsigned) time(nullptr));
}

void Network::gameLoop()
{
    auto start = std::chrono::steady_clock::now();
    long a = 0;
    setUpEcs();
    gCoordinator.AddComponent<std::shared_ptr<enemyComp>>(gCoordinator.CreateEntity(), std::make_shared<enemyComp>(Vector2f(1000, 500), _udp_server.enemySys->getNewId(0), 5, 0));
    gCoordinator.AddComponent<std::shared_ptr<enemyComp>>(gCoordinator.CreateEntity(), std::make_shared<enemyComp>(Vector2f(800, 200), _udp_server.enemySys->getNewId(0), 5, 0));
    gCoordinator.AddComponent<std::shared_ptr<enemyComp>>(gCoordinator.CreateEntity(), std::make_shared<enemyComp>(Vector2f(720, 150), _udp_server.enemySys->getNewId(0), 5, 0));
    while (true) {
        auto timeSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        _udp_server.enemySys->move(timeSinceStart);
        for (const auto &endpoint: _udp_server._clients) {
            _udp_server.enemySys->sendPos(_udp_server._socket, endpoint);
        }
        if (a + 700 < timeSinceStart) {
            a = timeSinceStart;
            for (const auto &endpoint: _udp_server._clients)
                _udp_server.enemySys->enemyShoot(_udp_server._socket, endpoint);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

Network::Network(unsigned int port) : _io_context_server(),
                     _tcp_server(TCP_Server(_io_context_server)),
                     _udp_server(UDP_Server(_io_context_server, port))
{
    try
    {
        std::thread t1(&Network::callable, this);
        // std::cout the message from client socket
        gameLoop();
        t1.join();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

boost::asio::ip::tcp::socket &TCP_Connection::socket()
{
    return _socket;
}

void TCP_Connection::start()
{
    static int clientNb = 0;
    _message = std::string("160") + std::to_string(clientNb);
    clientNb++;
    boost::asio::async_write(_socket, boost::asio::buffer(_message),
                             boost::bind(&TCP_Connection::handleWrite, this, boost::asio::placeholders::error));
}

TCP_Connection::TCP_Connection(boost::asio::io_context &ioc) : _socket(ioc)
{
}

void TCP_Connection::handleWrite(const boost::system::error_code &ec)
{
    if (!ec)
    {
        std::cout << "New client connected" << std::endl;
    }
}

void UDP_Server::startReceive()
{
    _socket.async_receive_from(boost::asio::buffer(_recv_buffer), _remote_endpoint,
                               boost::bind(&UDP_Server::handleReceive,
                                           this,
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
}

int UDP_Server::getClientId(boost::asio::ip::udp::endpoint endpoint)
{
    int id = 0;
    for (auto it = _clients.begin(); it != _clients.end(); it++, id++)
        if (*it == endpoint)
            return id;
    return (-1);
}

void UDP_Server::handleSend(const boost::shared_ptr<std::string> str, const boost::system::error_code &ec, std::size_t bytes_transferred)
{
}