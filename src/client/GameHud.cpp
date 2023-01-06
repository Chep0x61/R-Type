/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Menu
*/

#include "client/GameGraphic.hpp"

Hud::Hud()
{
    _spacetime.loadFromFile("assets/fonts/spacetime-regular.ttf");

    _life.setString("100hp");
    _score.setString("0");
    _life.setFont(_spacetime);
    _score.setFont(_spacetime);
    _life.setCharacterSize(48);
    _score.setCharacterSize(48);
    _life.setFillColor(sf::Color::Yellow);
    _score.setFillColor(sf::Color::Yellow);
    _life.setPosition(1110, 2);
    _score.setPosition(10, 2);
}

void Hud::drawHud(std::shared_ptr<GameContainer> gameContainer)
{
    gameContainer->window->draw(_life);
    gameContainer->window->draw(_score);
}

void Hud::updateHud(int life, int score)
{
    if (life == -1)
        life = 0;
    _life.setString(std::to_string(life * 20) + "hp");
    _score.setString(std::to_string(score));
}