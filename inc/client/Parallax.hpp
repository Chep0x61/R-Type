/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Parallax
*/

/**
 * @file Parallax.hpp
 * @brief Parallax
 */

#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <stdexcept>
#include "Coordinator.hpp"
extern ecs::Coordinator gCoordinator;

/**
 * @class ParallaxComp
 * @brief Parallax Component
 */
class ParallaxComp {
    public:
        ParallaxComp(std::string filepath, float speedMove);
        sf::Sprite sprite1;
        sf::Sprite sprite2;
        float speedMove;
    private:
        sf::Texture _texture;
};

/**
 * @class ParallaxSys
 * @brief Parallax System
 */
class ParallaxSys : public ecs::System {
    public:
        /**
         * @brief Move and draw
         * @param window
         */
        void MoveAndDraw(std::shared_ptr<sf::RenderWindow> window);
};