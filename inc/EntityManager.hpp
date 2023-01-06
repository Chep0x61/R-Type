/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** EntityManager header file
*/

/**
 * @file EntityManager.hpp
 * @brief Manager handling entities
 */

#pragma once

#include <array>
#include <iostream>
#include <stdlib.h>
#include <queue>
#include "Entity.hpp"
#include "Signature.hpp"

/**
 * @file Coordinator.hpp
 * @brief Combine and handling each manager
 */

/**
 * @namespace ecs
 * @brief Entity Component System
 */
namespace ecs {
    /**
     * @brief Manager handling entities
     */
    class EntityManager {
     public:
      /**
       * @brief Initialise the manager
       */
      EntityManager();
        /**
         * @brief Create an entity
         * @return Entity
         */
      Entity CreateEntity();
        /**
         * @brief Destroy an entity
         * @param Entity entity
         */
      void DestroyEntity(Entity entity);
        /**
         * @brief Set the signature of an entity
         * @param Entity entity, Signature signature
         */
      void SetSignature(Entity entity, Signature signature);
        /**
         * @brief Get the signature of an entity
         * @param Entity entity
         * @return Signature
         */
      Signature GetSignature(Entity entity);

 private:
  std::array<Signature, MAX_ENTITIES> _mSignatures;
  std::queue<Entity> _mAvailableEntities;
  uint32_t _mLivingEntityCount{};
};
}  // namespace ecs
