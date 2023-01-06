/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** SpaceShip
*/

/**
 * @file SpaceShip.hpp
 * @brief SpaceShip
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
#include "utils/Vector.hpp"
#include "utils/Direction.hpp"
#include "client/Bullets.hpp"

void createSpaceShip(const std::string& filePath, sf::Vector2f pos, int id, bool isPlayer);

/**
 * @class SpaceShipComp
 * @brief SpaceShip Component
 */
class SpaceShipComp {
    public:
        /**
         * @brief Construct a new Space Ship Comp object
         *
         * @param filepath
         * @param filepathBullet
         * @param nbPlayer
         * @param isPlayer
         *
         * @return SpaceShipComp
         */
        SpaceShipComp(std::string filepath, std::string filepathBullet, int nbPlayer, bool isPlayer);
        /**
         * @brief Shoot function
         */
        void shoot(const sf::Sprite& spriteShooting);


        sf::Sprite sprite;
        int32_t lastShoot = 0;
        bool isPlayer;
        bool isShooting;
        std::vector<sf::Sprite> bullets;
        int nbPlayer;
        sf::SoundBuffer buffer;
        sf::Sound sound;
    private:
        sf::Texture _texture;
        sf::Texture _bulletTexture;
};

/**
 * @class SpaceShipSys
 * @brief SpaceShip System
 */
class SpaceShipSys: public ecs::System {
    public:
        /**
         * @brief Animation
         * @param gameContainer
         */
        void animAndDraw(const std::shared_ptr<GameContainer>& gameContainer);
        /**
         * @brief Move
         * @param delta
         */
        void move(const std::shared_ptr<GameContainer>& gameContainer);
        /**
         * @brief Shoot
         * @param clock
         */
        void shoot(const std::shared_ptr<GameContainer>& gameContainer);
        /**
         * @brief Get player
         * @return std::shared_ptr<SpaceShipComp>
         */
        void destroySpaceShip(int id);
        void checkCollision(std::shared_ptr<BulletSys> bulletSys, int &life);
        std::shared_ptr<SpaceShipComp> getPlayer();
        std::shared_ptr<sf::Sprite> getPlayerSprite();
        std::shared_ptr<sf::Sprite> getSpriteByid(int id);
        /**
         * @brief Get player by id
         * @param id
         * @return std::shared_ptr<SpaceShipComp>
         */
        std::shared_ptr<SpaceShipComp> getPlayerById(int id);
        /**
         * @brief Remove
         * @param id>
         */
        void removePlayer(int id);

        void setPosition(int id, sf::Vector2f pos);

};
