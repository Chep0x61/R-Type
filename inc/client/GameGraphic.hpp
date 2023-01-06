/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** GameGraphic
*/

/**
 * @file GameGraphic.hpp
 * @brief GameGraphic
 */

#ifndef GAMEGRAPHIC_HPP_
#define GAMEGRAPHIC_HPP_
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Coordinator.hpp"
#include "client/Button.hpp"
#include "client/Parallax.hpp"
#include "client/SpaceShip.hpp"
#include "client/GameContainer.hpp"
#include "client/interactServer.hpp"
#include "client/Ennemy.hpp"
#include "utils/Vector.hpp"
#include "Bullets.hpp"

/**
 * @brief Create a sprite and a texture
 */
class SprTxt {
    public:
        SprTxt(const std::string& filepath);

        std::shared_ptr<sf::Sprite> sprite;
        std::shared_ptr<sf::Texture> texture;
};

/**
 * @brief GameGraphic
 */
class IGameContext {
    public:
        /**
         * @brief GameLoop
         * @param gameContainer
         * @return virtual bool
         */
        virtual bool gameLoop(std::shared_ptr<GameContainer> gameContainer) = 0;
        virtual bool eventHandler(std::shared_ptr<GameContainer> gameContainer) = 0;
        virtual bool isMenu() = 0;
        /**
         * @brief Initialize the game container
         * @param gameContainer
         * @return virtual bool
         */
        virtual void Init(std::shared_ptr<GameContainer> gameContainer) = 0;
        virtual void Quit() = 0;
        /**
         * @brief Check if the server is running
         * @param Server
         * @return virtual bool
         */
        virtual void Server() = 0;

    private:
};

/**
 * @brief Menu
 */
class Menu: public IGameContext {
    public:
        /**
         * @brief Menu constructor
         * @return Menu
         */
        Menu();
        /**
         * @brief GameLoop
         * @param gameContainer
         * @return bool
         */
        bool gameLoop(std::shared_ptr<GameContainer> gameContainer);
        bool eventHandler(std::shared_ptr<GameContainer> gameContainer);
        bool isMenu();
        void Quit(){}
        /**
         * @brief Initialize the menu
         * @param gameContainer
         */
        void Init(std::shared_ptr<GameContainer> gameContainer){}
        /**
         * @brief Server checker
         * @param Server
         */
        void Server() {}
        sf::Sprite spriteSingle;
        sf::Sprite spriteMulti;
        sf::Sprite spriteLogo;
        sf::Music _music;
    private:
        std::shared_ptr<buttonSys> _buttonSys;
        sf::Texture _textureBnSingle;
        sf::Texture _textureBnMulti;
        sf::Texture _textureBaSingle;
        sf::Texture _textureBaMulti;
        sf::Texture _textureLogo;
};

/**
 * @brief Hud
 * @return Hud informations
 */
class Hud {
    public:
        Hud();
        void drawHud(std::shared_ptr<GameContainer> gameContainer);
        void updateHud(int life, int score);
    private:
        sf::Text _life;
        sf::Text _score;
        sf::Font _spacetime;
};

/**
 * @brief Game
 */
class Game: public IGameContext {
    public:
        /**
         * @brief Game constructor
         * @return Game
         */
        Game();
        /**
         * @brief GameLoop
         * @param gameContainer
         * @return bool
         */
        bool gameLoop(std::shared_ptr<GameContainer> gameContainer);
        bool eventHandler(std::shared_ptr<GameContainer> gameContainer);
        void Init(std::shared_ptr<GameContainer> gameContainer);
        void Quit();
        /**
         * @brief Initialize the game server
         * @return bool
         */
        void Server();
        /**
         * @brief Check if the menu is active
         * @return bool
         */
        bool isMenu();
        /**
         * @brief Check remaining life
         * @return int
         */
        int getLife();
        /**
         * @brief Set the life
         * @param life
         */
        void setLife(int life);

private:
    sf::Clock _clock;
    std::shared_ptr<SpaceShipSys> _spaceShipSys;
    std::shared_ptr<EnnemySys> _ennemySys;
    std::shared_ptr<BulletSys> _bulletSys;
    std::shared_ptr<InteractServer> _interactServer;
    Hud _hud;
    sf::Music _music;
    int _life;
    int _score;
};

/**
 * @class GameGraphic
 * @brief GameGraphic
 */
class GameGraphic
{

public:
    /**
     * @brief GameGraphic constructor
     * @return GameGraphic
     */
    GameGraphic();
    /**
     * @brief Graphic loop
     */
    void loop();
    /**
     * @brief Event handler
     * @return bool
     */
    bool eventHandler();
    /**
     * @brief CGet the shared container
     * @return std::shared_ptr<IGameContainer>
     */
    std::shared_ptr<GameContainer> _container;
    bool isKeyPressed[sf::Keyboard::Key::KeyCount];

private:
    std::shared_ptr<IGameContext> _gameContext;
    std::shared_ptr<ParallaxSys> _parallaxSys;
};

#endif /* !GAMEGRAPHIC_HPP_ */
