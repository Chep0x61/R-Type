/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Ennemy
*/

#include "client/Ennemy.hpp"

EnnemyComp::EnnemyComp(std::string filepath, ENNEMY_TYPE type, sf::Vector2f position, unsigned int id) : id(id)
{
    if (!_texture.loadFromFile(filepath))
        throw std::runtime_error("Couldn't load spaceship texture from file " + filepath);
    sprite.setTexture(_texture);
    sprite.setPosition(position);
    sprite.setScale({3, 3});
    ennemyType = type;
    if (type == 0)
        sprite.setTextureRect({{0, 0}, {33, 36}});
}

TextureComp::TextureComp(std::string filepath)
{
    if (!texture.loadFromFile(filepath))
        throw std::runtime_error("Couldn't load spaceship texture from file: " + filepath);
}

void EnnemySys::drawEnnemies(std::shared_ptr<GameContainer> gameContainer)
{
//    std::cout << mapEntities.size() << std::endl;
    for (auto entity = mapEntities.begin(); entity != mapEntities.end(); ++entity) {
        std::shared_ptr<EnnemyComp> ennemy = gCoordinator.GetComponent<std::shared_ptr<EnnemyComp>>(*entity);
        if (ennemy->ennemyType == 0) {
            sf::IntRect rect = ennemy->sprite.getTextureRect();
            rect.left = gameContainer->clock.getElapsedTime().asMilliseconds() / 200 % 7 * 33;
            ennemy->sprite.setTextureRect(rect);
        }
        gameContainer->window->draw(ennemy->sprite);
    }
}

std::shared_ptr<EnnemyComp> EnnemySys::getEnnemyById(int id)
{
    for (auto entity = mapEntities.begin(); entity != mapEntities.end(); ++entity) {
        std::shared_ptr<EnnemyComp> ennemy = gCoordinator.GetComponent<std::shared_ptr<EnnemyComp>>(*entity);
        if (ennemy->id == id)
            return ennemy;
    }
    return nullptr;
}

void EnnemySys::checkCollision(const std::shared_ptr<BulletSys>& bulletSys, int &score)
{
    std::vector<unsigned int> entityToDestroy;
    for (unsigned int entity : mapEntities) {
        std::shared_ptr<EnnemyComp> ennemy = gCoordinator.GetComponent<std::shared_ptr<EnnemyComp>>(entity);
        if (bulletSys->bulletTouch(ennemy->sprite, false)) {
            enemiesTouched.push_back(ennemy->id);
            score += 20;
        }
        bulletSys->bulletTouch(ennemy->sprite, true);
    }
}
