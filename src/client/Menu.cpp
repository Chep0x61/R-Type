/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Menu
*/

#include "client/GameGraphic.hpp"

Menu::Menu()
{
    std::string filepathBnMulti = "assets/menu/bn_multi.png";
    std::string filepathBnSingle = "assets/menu/bn_single.png";
    std::string filepathBaMulti = "assets/menu/ba_multi.png";
    std::string filepathBaSingle = "assets/menu/ba_single.png";
    std::string filepathLogo = "assets/menu/logo.png";
    std::string filepathMusic = "assets/music/main_menu/main_menu.wav";
    if (!_textureBnSingle.loadFromFile(filepathBnSingle))
        throw std::runtime_error("Couldn't load buton texture from file " + filepathBnSingle);
    if (!_textureBnMulti.loadFromFile(filepathBnMulti))
        throw std::runtime_error("Couldn't load button texture from file " + filepathBnMulti);
    if (!_textureBaSingle.loadFromFile(filepathBaSingle))
        throw std::runtime_error("Couldn't load buton texture from file " + filepathBaSingle);
    if (!_textureBaMulti.loadFromFile(filepathBaMulti))
        throw std::runtime_error("Couldn't load button texture from file " + filepathBaMulti);
    if (!_textureLogo.loadFromFile(filepathLogo))
        throw std::runtime_error("Couldn't load buton texture from file " + filepathLogo);
    if (!_music.openFromFile(filepathMusic))
        throw std::runtime_error("Couldn't open" + filepathMusic + "file");
    _music.setLoop(true);
    _music.setVolume(50);
    _music.play();
    spriteSingle.setTexture(_textureBnSingle);
    spriteMulti.setTexture(_textureBnMulti);
    spriteLogo.setTexture(_textureLogo);
    spriteSingle.setPosition({470, 300});
    spriteMulti.setPosition({470, 450});
    spriteLogo.setPosition({400, 100});
    spriteSingle.setScale({3, 3});
    spriteMulti.setScale({3, 3});
    spriteLogo.setScale({0.5, 0.5});
}

bool Menu::gameLoop(std::shared_ptr<GameContainer> gameContainer)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*gameContainer->window);
    sf::Vector2f spriteSinglePos = spriteSingle.getPosition();
    sf::Vector2f spriteMultiPos = spriteMulti.getPosition();
    
    if (spriteSingle.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y))
        spriteSingle.setTexture(_textureBaSingle);
    else
        spriteSingle.setTexture(_textureBnSingle);
    
    if (spriteMulti.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y)) {
        spriteMulti.setTexture(_textureBaMulti);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            return true;
    }
    else
        spriteMulti.setTexture(_textureBnMulti);

    gameContainer->window->draw(spriteSingle);
    gameContainer->window->draw(spriteMulti);
    gameContainer->window->draw(spriteLogo);
    return false;
}

bool Menu::eventHandler(std::shared_ptr<GameContainer> gameContainer)
{
    return false;
}

bool Menu::isMenu()
{
    return true;
}