/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** ecs tests
*/

#include "ecs/EntityManager.cpp"
#include <gtest/gtest.h>

TEST(EntityManager, Creation)
{
    ecs::EntityManager manager;

    ASSERT_EQ(0, manager.CreateEntity());
    manager.DestroyEntity(0);
    ASSERT_NE(0, manager.CreateEntity());
}