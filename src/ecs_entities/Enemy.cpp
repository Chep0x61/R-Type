#include "ecs/Enemy.hpp"
#include "Coordinator.hpp"

enemyComp::enemyComp(Vector2f pos, unsigned int id, unsigned int life, unsigned int type): pos(pos), BasePos(pos), id(id), life(life), type(type)
{

}

void EnemySys::move(long timeMs) {
    for (unsigned int entity : mapEntities) {
        std::shared_ptr<enemyComp> enemy = gCoordinator.GetComponent<std::shared_ptr<enemyComp>>(entity);
        if (enemy->type == 1) {
            enemy->pos.y = std::cos((float)((double)timeMs * 0.001 + enemy->id * 2)) * 290 + 300;
            continue;
        }
        enemy->pos.x = std::cos((float)((double)timeMs * 0.002 * (enemy->id % 2 == 0 ? 1 : -1) + enemy->id)) * 200 + enemy->BasePos.x;
        enemy->pos.y = std::sin((float)((double)timeMs * 0.002 * (enemy->id % 2 == 0 ? 1 : -1) + enemy->id)) * 150 + enemy->BasePos.y;
    }
}

bool EnemySys::enemyTouched(int id) {
    for (unsigned int entity : mapEntities) {
        std::shared_ptr<enemyComp> enemy = gCoordinator.GetComponent<std::shared_ptr<enemyComp>>(entity);
        if (enemy->id == id) {
            enemy->life--;
            if (enemy->life == 0) {
                gCoordinator.DestroyEntity(entity);
                gCoordinator.AddComponent<std::shared_ptr<enemyComp>>(gCoordinator.CreateEntity(), std::make_shared<enemyComp>(Vector2f((float)(500 + rand() % 570), (float)(150 + rand() % 400)), getNewId(enemy->type), 5, enemy->type));
                return true;
            }
        }
    }
    return false;
}

void EnemySys::sendPos(boost::asio::basic_datagram_socket <boost::asio::ip::udp> &socket, const boost::asio::ip::basic_endpoint <boost::asio::ip::udp> &endpoint)
{
    for (unsigned int entity : mapEntities) {
        std::shared_ptr<enemyComp> enemy = gCoordinator.GetComponent<std::shared_ptr<enemyComp>>(entity);
        socket.send_to(boost::asio::buffer(std::string("121") + std::to_string(enemy->id) + std::to_string(enemy->type) + std::to_string(enemy->pos.x) + ";" + std::to_string(enemy->pos.y)), endpoint);
    }
}

int EnemySys::getNewId(unsigned int type) {
    std::map<unsigned int, unsigned int> idTaken;
    for (int i = 0; i < 10; i++) {
        bool taken = false;
        for (unsigned int entity: mapEntities) {
            std::shared_ptr<enemyComp> enemy = gCoordinator.GetComponent<std::shared_ptr<enemyComp>>(entity);
                if (enemy->id == i) {
                    taken = true;
                    break;
                }
        }
        if (!taken)
            return i;
    }
    return 0;
}

void EnemySys::enemyShoot(boost::asio::basic_datagram_socket<boost::asio::ip::udp> &socket, const boost::asio::ip::basic_endpoint<boost::asio::ip::udp> &endpoint) {
    if (mapEntities.empty()) return;
    for (unsigned int entity : mapEntities) {
        bool random = rand() % 2;
        if (gCoordinator.GetComponent<std::shared_ptr<enemyComp>>(entity)->type == 0) {
            if (random)
                socket.send_to(boost::asio::buffer(std::string("122") + std::to_string(
                                       gCoordinator.GetComponent<std::shared_ptr<enemyComp>>(entity)->id)),
                               endpoint);
        } else
            socket.send_to(boost::asio::buffer(std::string("122") + std::to_string(
                                       gCoordinator.GetComponent<std::shared_ptr<enemyComp>>(entity)->id)),
                               endpoint);
    }
}

