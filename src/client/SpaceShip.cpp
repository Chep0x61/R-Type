/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-kylian.paulin
** File description:
** SpaceShipp
*/

#include "client/SpaceShip.hpp"
#include "client/Ennemy.hpp"
#include "client/Texture.hpp"

void createSpaceShip(const std::string& filePath, sf::Vector2f pos, int id, bool isPlayer)
{
    static std::shared_ptr<sf::Texture> PlayerTexture = [filePath](){
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(filePath))
            throw std::runtime_error("Could not load " + filePath);
        return texture;
    }();
    if (id >= 5) {
        std::cout << "cannot be more than 5 players" << std::endl;
        return;
    }
    Entity entity = gCoordinator.CreateEntity();
    std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>(*PlayerTexture);
    sprite->setPosition(pos);
    sprite->setTextureRect(sf::IntRect({66, 17 * id}, {33, 17}));
    sprite->setScale({3, 3});
    gCoordinator.AddComponent(entity, sprite);
    gCoordinator.AddComponent(entity, std::make_shared<SpaceShipComp>(filePath, "assets/character/bullet.png", id, isPlayer));
}

SpaceShipComp::SpaceShipComp(std::string filepath, std::string filepathBullet, int nbPlayer, bool isPlayer): isPlayer(isPlayer), nbPlayer(nbPlayer), isShooting(false)
{
    if (!_texture.loadFromFile(filepath) || !_bulletTexture.loadFromFile(filepathBullet))
        throw std::runtime_error("Couldn't load spaceship texture from file " + filepath);
    sprite.setTexture(_texture);
    sprite.setTextureRect(sf::IntRect({66, 17 * nbPlayer}, {33, 17}));
    sprite.setScale({3, 3});


    if (!buffer.loadFromFile("assets/sound_effect/player/player_basic_shot.wav"))
        throw std::runtime_error("Couldn't load player shot sound from file: " + filepath);
    sound.setBuffer(buffer);
    sound.setVolume(25);
}

void SpaceShipSys::animAndDraw(const std::shared_ptr<GameContainer>& gameContainer)
{
    for (unsigned int entity : mapEntities) {
        std::shared_ptr<sf::Sprite> sprite = gCoordinator.GetComponent<std::shared_ptr<sf::Sprite>>(entity);
        std::shared_ptr<SpaceShipComp> spaceShip = gCoordinator.GetComponent<std::shared_ptr<SpaceShipComp>>(entity);
        gameContainer->window->draw(*sprite);
        for (auto & bullet : spaceShip->bullets) {
            bullet.move({(float)gameContainer->delta, 0});
            gameContainer->window->draw(bullet);
        }
        spaceShip->bullets.erase(std::remove_if(spaceShip->bullets.begin(), spaceShip->bullets.end(), [](const sf::Sprite &bullet) {
            return bullet.getPosition().x > 1280;
        }),
        spaceShip->bullets.end());
    }
}

void SpaceShipSys::move(const std::shared_ptr<GameContainer>& gameContainer)
{
    float movePixels = gameContainer->delta / 2;
    for (unsigned int entity : mapEntities) {
        std::shared_ptr<SpaceShipComp> spaceShip = gCoordinator.GetComponent<std::shared_ptr<SpaceShipComp>>(entity);
        std::shared_ptr<sf::Sprite> sprite = gCoordinator.GetComponent<std::shared_ptr<sf::Sprite>>(entity);
        if (!spaceShip->isPlayer)
            continue;
        sf::Vector2f pos = sprite->getPosition();
        sf::FloatRect size = sprite->getGlobalBounds();
        sprite->setTextureRect(sf::IntRect({66, 17 * spaceShip->nbPlayer}, {33, 17}));
        if (gameContainer->keyPressed[sf::Keyboard::Up] && pos.y > 0) {
            sprite->move({0, -movePixels});
            sprite->setTextureRect(sf::IntRect({99, 17 * spaceShip->nbPlayer}, {33, 17}));
        }
        if (gameContainer->keyPressed[sf::Keyboard::Left] && pos.x > 0)
            sprite->move({-movePixels, 0});
        if (gameContainer->keyPressed[sf::Keyboard::Down] && pos.y < 720 - size.height) {
            sprite->move({0, movePixels});
            sprite->setTextureRect(sf::IntRect({33, 17 * spaceShip->nbPlayer}, {33, 17}));
        }
        if (gameContainer->keyPressed[sf::Keyboard::Right] && pos.x < 1280 - size.width)
            sprite->move({movePixels, 0});
    }
}

void SpaceShipComp::shoot(const sf::Sprite& spriteShooting)
{
    sf::Vector2f pos = {spriteShooting.getPosition().x + spriteShooting.getGlobalBounds().width, spriteShooting.getPosition().y + spriteShooting.getGlobalBounds().height / 2};
    if (isPlayer)
        createBullet(pos, RIGHT, 5, false);
    else
        createBullet(pos, RIGHT, 5, true);
    sound.play();
}

void SpaceShipSys::destroySpaceShip(int id) {
    for (unsigned int entity : mapEntities) {
        std::shared_ptr<SpaceShipComp> spaceShip = gCoordinator.GetComponent<std::shared_ptr<SpaceShipComp>>(entity);
        if (id == spaceShip->nbPlayer) {
            gCoordinator.DestroyEntity(entity);
            return;
        }
    }
}

void SpaceShipSys::shoot(const std::shared_ptr<GameContainer>& gameContainer) {
    for (unsigned int entity : mapEntities) {

        std::shared_ptr<SpaceShipComp> spaceShip = gCoordinator.GetComponent<std::shared_ptr<SpaceShipComp>>(entity);
        std::shared_ptr<sf::Sprite> sprite = gCoordinator.GetComponent<std::shared_ptr<sf::Sprite>>(entity);
        if (!spaceShip->isPlayer)
            continue;
        if (gameContainer->keyPressed[sf::Keyboard::Space] && spaceShip->lastShoot + 200 < gameContainer->clock.getElapsedTime().asMilliseconds()) {
            spaceShip->shoot(*sprite);
            spaceShip->isShooting = true;
            spaceShip->lastShoot = gameContainer->clock.getElapsedTime().asMilliseconds();
        }
    }
}

std::shared_ptr<SpaceShipComp> SpaceShipSys::getPlayer()
{
    for (unsigned int entity : mapEntities) {
        std::shared_ptr<SpaceShipComp> spaceShip = gCoordinator.GetComponent<std::shared_ptr<SpaceShipComp>>(entity);
        if (spaceShip->isPlayer)
            return spaceShip;
    }
    return nullptr;
}

std::shared_ptr<SpaceShipComp> SpaceShipSys::getPlayerById(int id)
{
    for (unsigned int entity : mapEntities) {
        std::shared_ptr<SpaceShipComp> spaceShip = gCoordinator.GetComponent<std::shared_ptr<SpaceShipComp>>(entity);
        if (spaceShip->nbPlayer == id)
            return spaceShip;
    }
    return nullptr;
}

std::shared_ptr<sf::Sprite> SpaceShipSys::getPlayerSprite() {
    for (unsigned int entity : mapEntities) {
        std::shared_ptr<SpaceShipComp> spaceShip = gCoordinator.GetComponent<std::shared_ptr<SpaceShipComp>>(entity);
        if (spaceShip->isPlayer)
            return gCoordinator.GetComponent<std::shared_ptr<sf::Sprite>>(entity);
    }
    return nullptr;
}

std::shared_ptr<sf::Sprite> SpaceShipSys::getSpriteByid(int id) {
    for (unsigned int entity : mapEntities) {
        std::shared_ptr<SpaceShipComp> spaceShip = gCoordinator.GetComponent<std::shared_ptr<SpaceShipComp>>(entity);
        if (spaceShip->nbPlayer == id)
            return gCoordinator.GetComponent<std::shared_ptr<sf::Sprite>>(entity);
    }
    return nullptr;
}


void SpaceShipSys::setPosition(int id, sf::Vector2f pos) {
    for (unsigned int entity : mapEntities) {
        if (gCoordinator.GetComponent<std::shared_ptr<SpaceShipComp>>(entity)->nbPlayer != id) continue;
        std::shared_ptr<sf::Sprite> sprite = gCoordinator.GetComponent<std::shared_ptr<sf::Sprite>>(entity);
        sprite->setPosition(pos);
    }
}

void SpaceShipSys::checkCollision(std::shared_ptr<BulletSys> bulletSys, int &life) {

    for (unsigned int entity : mapEntities) {
        std::shared_ptr<SpaceShipComp> spaceShip = gCoordinator.GetComponent<std::shared_ptr<SpaceShipComp>>(entity);
        std::shared_ptr<sf::Sprite> sprite = gCoordinator.GetComponent<std::shared_ptr<sf::Sprite>>(entity);
        if (bulletSys->bulletTouch(*sprite, true) && spaceShip->isPlayer)
            std::cout << "Bullet touched, life left: " << --life << std::endl;
        if (!spaceShip->isPlayer)
            bulletSys->bulletTouch(*sprite, false);
    }
}
