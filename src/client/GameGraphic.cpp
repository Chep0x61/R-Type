/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** GameGraphic
*/

#include <memory>
#include <thread>
#include "client/GameGraphic.hpp"
#include "client/GameContainer.hpp"

GameGraphic::GameGraphic()
{
    _gameContext = std::make_shared<Menu>();
    _container = std::make_shared<GameContainer>();

    //Create Parallax
    _parallaxSys = gCoordinator.RegisterSystem<ParallaxSys>();
    gCoordinator.RegisterComponent<std::shared_ptr<ParallaxComp>>();
    Signature signature;
    gCoordinator.setSystemSignature<ParallaxSys>(signature.set(gCoordinator.GetComponentType<std::shared_ptr<ParallaxComp>>()));
    gCoordinator.AddComponent(gCoordinator.CreateEntity(), std::make_shared<ParallaxComp>("assets/screens/back1.png", 1.5));
    gCoordinator.AddComponent(gCoordinator.CreateEntity(), std::make_shared<ParallaxComp>("assets/screens/back4.png", 1));
}

bool GameGraphic::eventHandler()
{
    while (_container->window->pollEvent(*_container->event)) {
        if (_container->event->type == sf::Event::Closed) {
            _container->window->close();
            return true;
        }
        if (_container->event->type == sf::Event::Resized) {
            sf::Vector2f newPos;
            if (_container->event->size.width > 1280)
                newPos.x = -(float)(_container->event->size.width - 1280) / 2;
            if (_container->event->size.height > 720)
                newPos.y = -(float)(_container->event->size.height - 720) / 2;
            sf::FloatRect visibleArea(newPos, {(float)_container->event->size.width, (float)_container->event->size.height});
            _container->window->setView(sf::View(visibleArea));
        }
        _container->updateKeys();
        _gameContext->eventHandler(_container);
    }
    return false;
}

void fixResize(std::shared_ptr<sf::RenderWindow> window)
{
    sf::RectangleShape rectangle(sf::Vector2f(1280, 720));
    rectangle.setPosition({-1280, 0});
    rectangle.setFillColor(sf::Color::Black);
    sf::RectangleShape rectangle2(sf::Vector2f(1280, 720));
    rectangle2.setPosition({1280, 0});
    rectangle2.setFillColor(sf::Color::Black);
    window->draw(rectangle);
    window->draw(rectangle2);
}

void GameGraphic::loop() {
    this->_gameContext->Init(this->_container);
    std::shared_ptr<std::thread> thr;
    while (_container->window->isOpen()) {
        _container->window->clear();
        _container->updateDelta();
        _container->removeKeyTap();
        _parallaxSys->MoveAndDraw(_container->window);
        if (_gameContext->gameLoop(_container)) {
            if (_gameContext->isMenu()) {
                _gameContext = std::shared_ptr<IGameContext>(new Game());
                this->_gameContext->Init(this->_container);
                thr = std::make_shared<std::thread>(
                        [this] { this->_gameContext->Server(); });
            } else {
                _gameContext = std::shared_ptr<IGameContext>(new Menu);
                this->_gameContext->Init(this->_container);
            }
            continue;
        }
        if (eventHandler()) {
            _gameContext->Quit();
            break;
        }
        fixResize(_container->window);
        _container->window->display();
    }
    if (thr != nullptr)
        thr->join();
}
