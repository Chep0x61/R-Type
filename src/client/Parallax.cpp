/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Parallax
*/

#include "client/Parallax.hpp"

ParallaxComp::ParallaxComp(std::string filepath, float speedMove): speedMove(speedMove)
{
    if (_texture.loadFromFile(filepath)) {
        sprite1.setTexture(_texture);
        sprite2.setTexture(_texture);
        sprite2.move({1280, 0});
    } else
        throw std::runtime_error("Couldn't load texture from file " + filepath);
}

void ParallaxSys::MoveAndDraw(std::shared_ptr<sf::RenderWindow> window)
{
    for (auto entity = mapEntities.begin(); entity != mapEntities.end(); ++entity) {
        std::shared_ptr<ParallaxComp> parallax = gCoordinator.GetComponent<std::shared_ptr<ParallaxComp>>(*entity);
        parallax->sprite1.move({-parallax->speedMove, 0});
        parallax->sprite2.move({-parallax->speedMove, 0});
        if (parallax->sprite1.getPosition().x < -1280) {
            parallax->sprite1.move({1280, 0});
            parallax->sprite2.move({1280, 0});
        }
        window->draw(parallax->sprite1);
        window->draw(parallax->sprite2);
    }
}
