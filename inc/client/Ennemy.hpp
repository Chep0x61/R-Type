/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Ennemy
*/

/**
 * @file Ennemy.hpp
 * @brief Ennemy
 */

#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <algorithm>
#include "Coordinator.hpp"
#include "client/GameContainer.hpp"
#include "client/Texture.hpp"
#include "client/Bullets.hpp"

enum ENNEMY_TYPE {
    BASIC_ENNEMY
};

/**
 * @class EnnemyComp
 * @brief Ennemy Component
 */
class EnnemyComp {
    public:
        /**
         * @brief Construct a new Ennemy Comp object
         *
         * @param filepath
         * @param type
         * @param position
         * @param id
         *
         * @return EnnemyComp
         */
        EnnemyComp(std::string filepath, ENNEMY_TYPE type, sf::Vector2f position, unsigned int id);

        ENNEMY_TYPE ennemyType;
        sf::Sprite sprite;
        unsigned int id;
        int life = 3;

    private:
        sf::Texture _texture;
};

/**
 * @class EnnemySys
 * @brief Ennemy System
 */
class EnnemySys: public ecs::System {
    public:
        /**
         * @brief Ennemies drawer
         *
         * @param gameContainer
         */
        void drawEnnemies(std::shared_ptr<GameContainer> gameContainer);
        /**
         * @brief Ennemies comp
         *
         * @param id
         *
         * @return std::shared_ptr<EnnemyComp>
         */
        std::shared_ptr<EnnemyComp> getEnnemyById(int id);
        std::vector<unsigned int> enemiesTouched;
        void checkCollision(const std::shared_ptr<BulletSys>& bulletSys, int &score);
};
