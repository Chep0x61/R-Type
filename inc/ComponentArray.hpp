/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Component Array
*/

/**
 * @file ComponentArray.hpp
 * @brief Array holding components
 */

#pragma once

#include "Component.hpp"
#include "Entity.hpp"
#include "EntityManager.hpp"
#include <cassert>
#include <unordered_map>

/**
 * @namespace ecs
 * @brief Entity Component System
 */
namespace ecs
{
    /**
     * @class IComponentArray
     * @brief Setup core of ArrayComponent throw Interface
     */
    class IComponentArray
    {
    public:
        /**
         * @brief IComponentArray Constructor
         */
        IComponentArray() {}
        /**
         * @brief IComponentArray Destructor
         */
        virtual ~IComponentArray() = default;
        /**
         * @brief Delete Entity
         * @param Entity entity
         */
        virtual void EntityDestroyed(Entity entity) = 0;
        /**
         * @brief Delete Reference IComponentArray
         * @param const IComponentArray &
         * @return IComponentArray
         */
        IComponentArray &operator=(const IComponentArray &) = delete;
        /**
         * @brief Delete Reference IComponent
         * @param const IComponentArray &
         * @return IComponentArray
         */
        IComponentArray(const IComponentArray &) = delete;
        /**
         * @brief Delete Double Reference IComponent
         * @param IComponentArray &&
         * @return IComponentArray
         */
        IComponentArray &operator=(IComponentArray &&) = delete;
    };

    /**
     * @class ComponentArray
     * @brief Array holding components
     * Inherits from IComponentArray Class
     */
    template <typename T>
    class ComponentArray : public IComponentArray
    {
    public:
        /**
         * @brief ComponentArray Constructor
         */
        ComponentArray() {}
        /**
         * @brief ComponentArray Destructor
         */
        ~ComponentArray() = default;
        /**
         * @brief Insert Data
         * Set Component inside ComponentArray
         * @param entity Entity
         * @param component Component
         */
        void InsertData(Entity entity, T component)
        {
            assert(_mEntityToIndexMap.find(entity) == _mEntityToIndexMap.end() && "Component added to same entity more than once.");
            size_t newIndex = _mSize;
            _mEntityToIndexMap[entity] = newIndex;
            _mIndexToEntityMap[newIndex] = entity;
            _mComponentArray[newIndex] = component;
            _mSize += 1;
        }

        /**
         * @brief Remove Data
         * Remove a specific Component of the ComponentArray
         * @param entity Entity
         */
        void RemoveData(Entity entity)
        {
            assert(_mEntityToIndexMap.find(entity) != _mEntityToIndexMap.end() && "Removing non-existent component.");
            size_t indexOfRemovedEntity = _mEntityToIndexMap[entity];
            size_t indexOfLastElement = _mSize - 1;
            _mComponentArray[indexOfRemovedEntity] = _mComponentArray[indexOfLastElement];
            Entity entityOfLastElement = _mIndexToEntityMap[indexOfLastElement];
            _mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            _mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;
            _mEntityToIndexMap.erase(entity);
            _mIndexToEntityMap.erase(indexOfLastElement);
            _mSize -= 1;
        }

        /**
         * @brief Get Data
         * Get data on a specific entity inside ComponentArray
         * @param entity Entity
         * @return T&
         */
        T& GetData(Entity entity)
        {
            assert(_mEntityToIndexMap.find(entity) != _mEntityToIndexMap.end() && "Retrieving non-existent component.");
            return _mComponentArray[_mEntityToIndexMap[entity]];
        }

        /**
         * @brief Delete Entity
         * Destroy a specific entity in ComponentArray
         * @param entity Entity
         */
        void EntityDestroyed(Entity entity) override
        {
            if (_mEntityToIndexMap.find(entity) != _mEntityToIndexMap.end())
            {
                RemoveData(entity);
            }
        }

    private:
        std::array<T, MAX_ENTITIES> _mComponentArray;
        std::unordered_map<Entity, size_t> _mEntityToIndexMap;
        std::unordered_map<size_t, Entity> _mIndexToEntityMap;
        size_t _mSize{};
    };
} // namespace ecs
