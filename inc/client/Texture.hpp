/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Texture
*/

/**
 * @file Texture.hpp
 * @brief Texture
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

enum TEXTURE_TYPE {
    ENNEMY
};

/**
 * @class TextureComp
 * @brief Texture Component
 */
class TextureComp {
    public:
        /**
         * @brief Construct a new Texture Comp object         *
         * @param filepath        *
         * @return TextureComp
         */
        TextureComp(std::string filepath);
        /**
         * @brief Construct a new Texture Comp object
         * @param typeT
         * @return TEXTURE_TYPE
         */
        TEXTURE_TYPE typeT;
        /**
         * @brief Construct a new Texture Comp object
         * @param texture
         * @return sf::Texture
         */
        sf::Texture texture;
};
