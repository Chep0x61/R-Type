/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** GameContainer
*/

#include "client/GameContainer.hpp"

GameContainer::GameContainer()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode({1280, 720}), "RTYPE");
    window->setFramerateLimit(60);
    window->setKeyRepeatEnabled(false);
    event = std::make_shared<sf::Event>();
}

void GameContainer::updateDelta()
{
    delta = _clockDelta.getElapsedTime().asMilliseconds();
    _clockDelta.restart();
}

void GameContainer::updateKeys()
{
    if (event->type == sf::Event::KeyPressed) {
        keyTap[event->key.code] = true;
        keyPressed[event->key.code] = true;
    }
    if (event->type == sf::Event::KeyReleased)
        keyPressed[event->key.code] = false;
}

void GameContainer::removeKeyTap()
{
    for (bool & i : keyTap)
        i = false;
}
