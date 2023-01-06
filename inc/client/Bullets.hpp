/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Bullets
*/

#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Coordinator.hpp"
#include "utils/Direction.hpp"
#include "client/GameContainer.hpp"

void createBullet(sf::Vector2f pos, Direction direction, int moveSpeed, bool isEnemy);

class BulletSys: public ecs::System {
public:
    void moveBullets(int32_t delta);
    bool bulletTouch(const sf::Sprite& sprite, bool isEnemyBullet);
    void drawBullets(const std::shared_ptr<GameContainer> &gameContainer);
};

// class BulletsComp {
//     public:
//         BulletsComp(std::shared_ptr<sf::Texture> texture);

//     private:
// };