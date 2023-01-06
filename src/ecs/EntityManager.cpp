/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** EntityManager
*/

#include "EntityManager.hpp"
using ecs::EntityManager;

EntityManager::EntityManager() {
    for (Entity entity = 0; entity < MAX_ENTITIES; entity += 1)
        _mAvailableEntities.push(entity);
}

Entity EntityManager::CreateEntity() {
    if (_mLivingEntityCount >= MAX_ENTITIES) {
      std::cerr << "Entity out of range" << std::endl;
      exit(84);
    }

    Entity id = _mAvailableEntities.front();
    _mAvailableEntities.pop();
    _mLivingEntityCount += 1;
    return id;
}

void EntityManager::DestroyEntity(Entity entity) {
    if (entity >= MAX_ENTITIES) {
      std::cerr << "Entity out of range" << std::endl;
      exit(84);
    }
    _mSignatures[entity].reset();
    _mAvailableEntities.push(entity);
    _mLivingEntityCount -= 1;
}

void EntityManager::SetSignature(Entity entity, Signature signature) {
    if (entity >= MAX_ENTITIES) {
      std::cerr << "Entity out of range" << std::endl;
      exit(84);
    }
    _mSignatures[entity] = signature;
}

Signature EntityManager::GetSignature(Entity entity) {
    if (entity >= MAX_ENTITIES) {
      std::cerr << "Entity out of range" << std::endl;
      exit(84);
    }
    return _mSignatures[entity];
}
