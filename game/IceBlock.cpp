//
// Created by chasi127 on 2019-12-08.
//

#include <SFML/Graphics.hpp>
#include <memory>
#include <random>

#include "IceBlock.h"
#include "Constants.h"
#include "GameState.h"

using dynamicObjPtr = std::shared_ptr<DynamicObject>;

///////////////////
// Constructor ///
//////////////////

IceBlock::IceBlock(sf::Vector2f const& position)
        : DynamicObject{{position}, 0, {0, 0}, 0, 90}, blockSize{}, hp{100}, age{100}
{
    std::random_device randomDevice;
    std::mt19937 generator{randomDevice()};
    std::uniform_int_distribution<int> blockSizes(1, 5);

    blockSize = blockSizes(generator);
    mass = blockSize * 1000;

    initializeTexture();
    setOrientation();
    setOrigin();
    setRadius();
}

IceBlock::IceBlock(sf::Vector2f const& position, float const mass,
                   sf::Vector2f const& speedDir)
        : DynamicObject{position, mass, {0, 0}, 0, 90}, clock{}, blockSize{}, hp{100}, age{0}
{
    blockSize = mass / 1000;
    initializeTexture();
    setRadius();
    setOrientation();
    setOrigin();
    normalizeSpeedDirection(speedDir);
}

/////////////////////////////
// Public member functions //
/////////////////////////////

void IceBlock::update(sf::View & view, GameState& world)
{
    sprite.rotate(0.5f);
    orientation = rotateVector(orientation,1);

    DynamicObject::update(view, world);
}

void IceBlock::collisionUpdate(GameState& world)
{
    hp -= 50;
    if(hp < 1)
    {
        alive = false;
        if(blockSize > 1)
        {
            splitIceBlock(world);
        }
    }
}

int IceBlock::getAge() const
{
    return age + clock.getElapsedTime().asSeconds();
}

//////////////////////////////
// Private member functions //
/////////////////////////////

void IceBlock::initializeTexture()
{
    sprite.setTexture(Constants::instance.textureIceBlock);
    sprite.setScale(0.2f + 0.06 * blockSize, 0.2f + 0.06 * blockSize);
}

void IceBlock::setRadius()
{
    sf::Vector2f size{sprite.getTexture() -> getSize()};
    radius = (size.x + size.y) / 4;
}

void IceBlock::setOrientation()
{
    sprite.rotate(1.0f);
    orientation = rotateVector(orientation,1);
}

void IceBlock::setOrigin()
{
    sf::Vector2f size{sprite.getTexture() -> getSize()};
    sprite.setOrigin(size.x/2, size.y/2);
}

void IceBlock::splitIceBlock(GameState& world)
{
    float newMass{};
    newMass = mass / 2;
    float remainder{};
    remainder = int(mass) % 2;

    /* New directions */
    sf::Vector2f newDirection1{rotateVector(direction, -45)};
    sf::Vector2f newDirection2{rotateVector(direction, 45)};

    /* Add two new ice blocks */
    sf::Vector2f newPosition1{sprite.getPosition() + newDirection1 * speed/float(Constants::instance.tickRate * 2)};
    sf::Vector2f newPosition2{sprite.getPosition() + newDirection2 * speed/float(Constants::instance.tickRate * 2)};

    sf::Vector2f newSpeedDir1 {newDirection1 * speed};
    sf::Vector2f newSpeedDir2 {newDirection2 * speed};
    world.addObject(dynamicObjPtr {new IceBlock{newPosition1, newMass, newSpeedDir1}});
    world.addObject(dynamicObjPtr {new IceBlock{newPosition2, newMass, newSpeedDir2}});

    /* Creates one more ice block if the rest is'nt 0 */
    if(remainder > 0)
    {
        sf::Vector2f newPosition3{sprite.getPosition() + direction * speed/float(Constants::instance.tickRate * 2)};
        sf::Vector2f newSpeedDir3 {direction * speed};
        world.addObject(dynamicObjPtr {new IceBlock{newPosition3, remainder, newSpeedDir3}});
    }
}