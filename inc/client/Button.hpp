/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** button
*/

/**
 * @file Button.hpp
 * @brief Button
 */

#pragma once
#include "System.hpp"
#include "Coordinator.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <string>

extern ecs::Coordinator gCoordinator;

/**
 * @class ButtonComp
 * @brief Button
 */
class ButtonComp{
    public:
         /**
         * @brief Button delete
         */
        ButtonComp() = delete;
        /**
         * @brief Button
         * @param texture
         * @param pos
         * @param size
         * @param text
         * @param font
         * @param color
         *
         * @return ButtonComp
         */
        ButtonComp(std::string filepath) {
            if (texture.loadFromFile(filepath))
                sprite.setTexture(texture);
        }
        /**
         * @brief Button texture
         * @param texture
         * @return sf::Texture
         */
        sf::Texture texture;
        /**
         * @brief Button sprite
         * @param sprite
         * @return sf::Sprite
         */
        sf::Sprite sprite;
};

/**
 * @class ButtonSys
 * @brief Button system
 */
class buttonSys: public ecs::System
{
    public:
        /**
         * @brief Button drawer
         */
        void drawButtons(std::shared_ptr<sf::RenderWindow> window) {
            for (auto entity = mapEntities.begin(); entity != mapEntities.end(); ++entity)
                window->draw(gCoordinator.GetComponent<std::shared_ptr<ButtonComp>>(*entity)->sprite);
        }
    private:
    
};
