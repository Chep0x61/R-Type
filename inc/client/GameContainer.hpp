/**
 * @file GameContainer.hpp
 * @brief GameContainer
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <iostream>

/**
 * @class GameContainer
 * @brief Game container
 */
class GameContainer
{
public:
    /**
     * @brief Constructor of the Game Container
     *
     * @return GameContainer
     */
    GameContainer();
    /**
     * @brief Render window
     * @param window
     * @return sf::RenderWindow
     */
    std::shared_ptr<sf::RenderWindow> window;
    /**
     * @brief Event handler
     * @param event
     * @return std::shared_ptr<sf::Event>
     */
    std::shared_ptr<sf::Event> event;
//    std::shared_ptr<InteractServer> _interactServer;
    char **argv;
    sf::Clock clock;
    int32_t delta;
    bool keyPressed[sf::Keyboard::KeyCount] = {};
    bool keyTap[sf::Keyboard::KeyCount] = {};
    /**
     * @brief Update Delta of the Game Container
     */
    void updateDelta();
    void updateKeys();
    void removeKeyTap();
    void Server();
    private:
        sf::Clock _clockDelta;

};
