/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Buttons
*/

#include <algorithm>
#include "client/Bullets.hpp"

void createBullet(sf::Vector2f pos, Direction direction, int moveSpeed, bool isEnemy)
{
    static std::shared_ptr<sf::Texture> BulletTexture = [](){
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("assets/character/bullet.png"))
            throw std::runtime_error(std::string("Could not load ") + "assets/character/bullet.png");
        return texture;
    }();
    static std::shared_ptr<sf::Texture> BulletTextureRev = [](){
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile("assets/character/bulletRev.png"))
            throw std::runtime_error(std::string("Could not load ") + "assets/character/bullet.png");
        return texture;
    }();
    Entity entity = gCoordinator.CreateEntity();
    std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>();
    if (direction == LEFT)
        sprite->setTexture(*BulletTextureRev);
    else
        sprite->setTexture(*BulletTexture);
    sprite->setPosition(pos);
    sprite->setScale({3, 3});
    gCoordinator.AddComponent(entity, sprite);
    gCoordinator.AddComponent(entity, std::make_shared<Direction>(direction));
    gCoordinator.AddComponent(entity, std::make_shared<float>(moveSpeed));
    gCoordinator.AddComponent(entity, std::make_shared<bool>(isEnemy));
}

void BulletSys::drawBullets(const std::shared_ptr<GameContainer>& gameContainer) {
    for (unsigned int entity : mapEntities)
        gameContainer->window->draw(*gCoordinator.GetComponent<std::shared_ptr<sf::Sprite>>(entity));
}

void BulletSys::moveBullets(int32_t delta) {
    delta /= 2;
    std::vector<unsigned int> entityToDestroy;
    for (unsigned int entity : mapEntities) {
        float moveSpeed = *gCoordinator.GetComponent<std::shared_ptr<float>>(entity) * (float)delta;
        Direction direction = *gCoordinator.GetComponent<std::shared_ptr<Direction>>(entity);
        std::shared_ptr<sf::Sprite> sprite = gCoordinator.GetComponent<std::shared_ptr<sf::Sprite>>(entity);
        if (direction == UP || direction == LEFT)
            moveSpeed *= -1;
        if (direction == DOWN || direction == UP)
            sprite->move({0, moveSpeed});
        else
            sprite->move({moveSpeed, 0});
        if (sprite->getPosition().x > 1280 || sprite->getPosition().x < -100 || sprite->getPosition().y > 720 || sprite->getPosition().y < -100)
            entityToDestroy.push_back(entity);
    }
    for (unsigned int entity : entityToDestroy)
        gCoordinator.DestroyEntity(entity);
}

bool BulletSys::bulletTouch(const sf::Sprite& sprite, bool isEnemyBullet) {
    for (unsigned int entity : mapEntities) {
        if (*gCoordinator.GetComponent<std::shared_ptr<bool>>(entity) == isEnemyBullet) {
            std::shared_ptr<sf::Sprite> entitySprite = gCoordinator.GetComponent<std::shared_ptr<sf::Sprite>>(entity);
            if (sprite.getGlobalBounds().intersects(entitySprite->getGlobalBounds())) {
                gCoordinator.DestroyEntity(entity);
                return true;
            }
        }
    }
    return false;
}
