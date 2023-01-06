/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** System header file
*/

/**
 * @file System.hpp
 * @brief System
 */

#pragma once

#include <set>
#include <memory>
#include "Entity.hpp"
#include "Component.hpp"

/**
 * @namespace ecs
 * @brief Entity Component System
 */
namespace ecs {
    /**
     * @brief System classs
     */
    class System {
        public:
            /**
             * @brief Set entity
             * @return std::set<Entity>
             */
            std::set<Entity> mapEntities;
    };
}  // namespace ecs
