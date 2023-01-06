/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** Game
*/

#include <future>
#include "client/GameGraphic.hpp"

Game::Game():
_spaceShipSys(gCoordinator.RegisterSystem<SpaceShipSys>()), _bulletSys(gCoordinator.RegisterSystem<BulletSys>()), _life(5), _score(0)
{
    gCoordinator.RegisterComponent<std::shared_ptr<SpaceShipComp>>();
    gCoordinator.RegisterComponent<std::shared_ptr<EnnemyComp>>();
    gCoordinator.RegisterComponent<std::shared_ptr<sf::Sprite>>();
    gCoordinator.RegisterComponent<std::shared_ptr<float>>();
    gCoordinator.RegisterComponent<std::shared_ptr<bool>>();
    gCoordinator.RegisterComponent<std::shared_ptr<Direction>>();
    Signature signature;
    signature.set(gCoordinator.GetComponentType<std::shared_ptr<SpaceShipComp>>());
    signature.set(gCoordinator.GetComponentType<std::shared_ptr<sf::Sprite>>());
    gCoordinator.setSystemSignature<SpaceShipSys>(signature);
    Signature signatureBullet;
    signatureBullet.set(gCoordinator.GetComponentType<std::shared_ptr<float>>());
    signatureBullet.set(gCoordinator.GetComponentType<std::shared_ptr<bool>>());
    signatureBullet.set(gCoordinator.GetComponentType<std::shared_ptr<sf::Sprite>>());
    signatureBullet.set(gCoordinator.GetComponentType<std::shared_ptr<Direction>>());
    gCoordinator.setSystemSignature<BulletSys>(signatureBullet);
    _ennemySys = gCoordinator.RegisterSystem<EnnemySys>();
    Signature signature2;
    gCoordinator.setSystemSignature<EnnemySys>(signature2.set(gCoordinator.GetComponentType<std::shared_ptr<EnnemyComp>>()));

    _interactServer = std::make_shared<InteractServer>(_spaceShipSys, _ennemySys);
    if (!_music.openFromFile("assets/music/level/level.wav"))
        throw std::runtime_error("Couldn't open level.wav file");
    _music.setLoop(true);
    _music.setVolume(10);
    _music.play();
}

void Game::Init(std::shared_ptr<GameContainer> gameContainer)
{
    _interactServer->createServer(gameContainer);
}

void Game::Server()
{
    _interactServer->ServerLoop();
}

bool Game::gameLoop(std::shared_ptr<GameContainer> gameContainer)
{
    _ennemySys->drawEnnemies(gameContainer);
    _hud.drawHud(gameContainer);
    _hud.updateHud(_life, _score);
    _spaceShipSys->animAndDraw(gameContainer);
    _bulletSys->moveBullets(gameContainer->delta);
    _bulletSys->drawBullets(gameContainer);
    _interactServer->life = _life;
    _spaceShipSys->move(gameContainer);
    _spaceShipSys->shoot(gameContainer);
    _spaceShipSys->checkCollision(_bulletSys, _life);
    _ennemySys->checkCollision(_bulletSys, _score);
    return false;
}

bool Game::eventHandler(std::shared_ptr<GameContainer> gameContainer)
{
    return false;
}

bool Game::isMenu()
{
    return false;
}

int Game::getLife()
{
    return _life;
}

void Game::setLife(int life)
{
    _life = life;
}

void Game::Quit() {
    _interactServer->Quit();
}
