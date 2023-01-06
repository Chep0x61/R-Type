/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** System
*/

#include "SystemManager.hpp"
#include "Signature.hpp"
#include "Entity.hpp"
using ecs::SystemManager;

void SystemManager::RemoveOldEntity(Entity entity) {
    for (auto & mapSystem : mapSystems)
        mapSystem.second->mapEntities.erase(entity);
}

void SystemManager::ChangedEntitySignature(Entity entity,
Signature entitySignature) {
    for (auto it = mapSystems.begin(); it != mapSystems.end(); ++it) {
        auto const systemSignature = mapSignatures[it->first];

        // compare each bit of the signature
        auto const signatureCmp = entitySignature & systemSignature;

        if (signatureCmp == systemSignature) {
            it->second->mapEntities.insert(entity);
        } else {
            it->second->mapEntities.erase(entity);
        }
    }
}
