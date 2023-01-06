/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Component Manager
*/

#include "ComponentManager.hpp"
using ecs::ComponentManager;

void ComponentManager::EntityDestroyed(Entity entity)
{
    for (auto const& pair : _mComponentArrays) {
	    auto const& component = pair.second;
	    component->EntityDestroyed(entity);
	}
}