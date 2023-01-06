/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Coordinator
*/

#include "Coordinator.hpp"
using ecs::Coordinator;

void Coordinator::Init()
{
    _mComponentManager = std::make_unique<ComponentManager>();
    _mEntityManager = std::make_unique<EntityManager>();
    _mSystemManager = std::make_unique<SystemManager>();
}

Entity Coordinator::CreateEntity()
{
    return _mEntityManager->CreateEntity();
}

void Coordinator::DestroyEntity(Entity entity)
{
    _mEntityManager->DestroyEntity(entity);
    _mComponentManager->EntityDestroyed(entity);
    _mSystemManager->RemoveOldEntity(entity);
}