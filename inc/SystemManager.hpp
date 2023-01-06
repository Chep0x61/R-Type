/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** SystemManager header file
*/

/**
 * @file SystemManager.hpp
 * @brief Manager handling systems
 */

#pragma once

#include <memory>
#include <bitset>
#include <cassert>
#include <unordered_map>
#include <stdexcept>
#include "Entity.hpp"
#include "Signature.hpp"
#include "System.hpp"

/**
 * @namespace ecs
 * @brief Entity Component System
 */
namespace ecs
{
   /**
    * @class SystemManager
    * @brief class representing the system manager
    */
    class SystemManager
   {
   public:
      /**
       * @brief Create a System
       * @return std::shared_ptr<T>
       */
      template <typename T>
      std::shared_ptr<T> CreateSystem()
      {
         const char *typeName = typeid(T).name();

         if (mapSystems.find(typeName) != mapSystems.end())
            throw std::runtime_error("Trying to create a system "
                                     "that already exist !");
         auto system = std::make_shared<T>();
         mapSystems.insert({typeName, system});
         return system;
      }
      /**
       * @brief Set Binary Signature to System
       * @param Signature : Binary Signature
       */
      template <typename T>
      void SetSystemSignature(Signature signature)
      {
         const char *typeName = typeid(T).name();

         if (mapSystems.find(typeName) == mapSystems.end())
            throw std::runtime_error("Trying to set system signature "
                                     "system not exist !");

         mapSignatures.insert({typeName, signature});
      }

      /**
       * @brief Remove a specific Entity
       * @param Entity entity
       */
      void RemoveOldEntity(Entity entity);
      /**
       * @brief Change Entity Signature
       * @param Entity entity
       * @param Signature : Current Signature Entity
       */
      void ChangedEntitySignature(Entity entity, Signature entitySignature);

   private:
      std::unordered_map<const char *, Signature> mapSignatures{};
      std::unordered_map<const char *, std::shared_ptr<System>> mapSystems{};
   };
} // namespace ecs
