/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Component Manager
*/

/**
 * @file ComponentManager.hpp
 * @brief Manager handling components
 */

#pragma once

#include <memory>
#include "Component.hpp"
#include "ComponentArray.hpp"
#include "Entity.hpp"
#include "Signature.hpp"

/**
 * @namespace ecs
 * @brief Entity Component System
 */
namespace ecs {
/**
 * @class ComponentManager
 * @brief Manager handling components
 */
class ComponentManager {
 public:
    /**
     * @brief Initialize a new component in ecs
     * @tparam T
     */
    template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();

    assert(_mComponentTypes.find(typeName) == _mComponentTypes.end() && "Registering component type more than once.");
    _mComponentTypes.insert({typeName, _mNextComponentType});
    _mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
    _mNextComponentType += 1;
	}

    /**
     * @brief Get a Component
     * @tparam T
     * @param component
     */
    template<typename T>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();

    assert(_mComponentTypes.find(typeName) != _mComponentTypes.end() && "Component not registered before use.");
	      return _mComponentTypes[typeName];
	}

    /**
     * @brief Add a component
     * @tparam T
     * @param entity, T component
     * @param component
     */
    template<typename T>
	void AddComponent(Entity entity, T component)
	{
		GetComponentArray<T>()->InsertData(entity, component);
	}

    /**
     * @brief Remove a component
     * @tparam T
     * @param entity
     */
    template<typename T>
	void RemoveComponent(Entity entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}

    /**
     * @brief Get a component
     * @tparam T
     * @param entity
     * @return T
     */
    template<typename T>
	T& GetComponent(Entity entity)
	{
		return GetComponentArray<T>()->GetData(entity);
	}

    /**
     * @brief Destroy an entity
     */
	void EntityDestroyed(Entity entity);

 private:
 	std::unordered_map<const char*, ComponentType> _mComponentTypes{};
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> _mComponentArrays{};
	ComponentType _mNextComponentType{};

    template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const char* typeName = typeid(T).name();

		assert(_mComponentTypes.find(typeName) != _mComponentTypes.end() && "Component not registered before use.");

		return std::static_pointer_cast<ComponentArray<T>>(_mComponentArrays[typeName]);
	}

};
}  // namespace ecs
