/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Coordinator
*/

/**
 * @file Coordinator.hpp
 * @brief Combine and handling each manager
 */

#pragma once

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

/**
 * @namespace ecs
 * @brief Entity Component System
 */
namespace ecs
{
    /**
     * @brief Combine and handling each manager
     */
    class Coordinator
    {
    public:
        //~Coordinator() {}
        /**
         * @brief Initialise the coordinator
         */
        void Init();
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
         * @brief Register a component
         * @param T
         */
        template <typename T>
        void RegisterComponent()
        {
            _mComponentManager->RegisterComponent<T>();
        }

        /**
         * @brief Add a component
         * @param T
         */
        template <typename T>
        void AddComponent(Entity entity, T component)
        {
            _mComponentManager->AddComponent<T>(entity, component);

            auto signature = _mEntityManager->GetSignature(entity);
            signature.set(_mComponentManager->GetComponentType<T>(), true);
            _mEntityManager->SetSignature(entity, signature);

            _mSystemManager->ChangedEntitySignature(entity, signature);
        }

        /**
         * @brief Remove a component
         * @param T
         */
        template <typename T>
        void RemoveComponent(Entity entity)
        {
            _mComponentManager->RemoveComponent<T>(entity);

            auto signature = _mEntityManager->GetSignature(entity);
            signature.set(_mComponentManager->GetComponentType<T>(), false);
            _mEntityManager->SetSignature(entity, signature);

            _mSystemManager->ChangedEntitySignature(entity, signature);
        }

        /**
         * @brief Get a component
         * @param Entity
         * @return T
         */
        template <typename T>
        T &GetComponent(Entity entity)
        {
            return _mComponentManager->GetComponent<T>(entity);
        }

        /**
         * @brief Get a component
         * @return ComponentType
         */
        template <typename T>
        ComponentType GetComponentType()
        {
            return _mComponentManager->GetComponentType<T>();
        }

        /**
         * @brief Register a system
         * @tparam T
         * @return std::shared_ptr<T>
         */
        template <typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            return _mSystemManager->CreateSystem<T>();
        }

        /**
         * @brief Set a system signature
         * @tparam T
         * @param signature
         */
        template <typename T>
        void setSystemSignature(Signature signature)
        {
            _mSystemManager->SetSystemSignature<T>(signature);
        }

    private:
        std::unique_ptr<ComponentManager> _mComponentManager;
        std::unique_ptr<EntityManager> _mEntityManager;
        std::unique_ptr<SystemManager> _mSystemManager;
    };
} // namespace ecs

extern ecs::Coordinator gCoordinator;
