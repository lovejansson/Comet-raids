//
// Created by love643 on 2019-12-11.
//

#include <SFML/Graphics.hpp>
#include <memory>

#include "Bomb.h"
#include "Explosion.h"
#include "Constants.h"
#include "GameState.h"

using staticObjPtr = std::shared_ptr<StaticObject>;

//////////////////
// Constructor //
/////////////////

Bomb::Bomb(sf::Vector2f const& position,
        sf::Vector2f const& direction, float const speed)
: DynamicObject{position, 500, direction, speed, 90}, clock{}, timerSec{3}, safe{true}
{
    initializeTexture();
    setOrigin();
    setRadius();
}

///////////////////////////////
// Public member functions ///
//////////////////////////////

void Bomb::update(sf::View & view, GameState & world)
{
    if(clock.getElapsedTime().asSeconds() >= timerSec )
    {
        safe = false;
    }
    DynamicObject::update(view, world);
}

void Bomb::collisionUpdate(GameState& world)
{
    if(!safe)
    {
        staticObjPtr newExplosion{new Explosion{{sprite.getPosition()}}};
        world.addObject(newExplosion);
        alive = false;
    }
}

//////////////////////////////
// Private member functions //
/////////////////////////////

void Bomb::initializeTexture()
{
    sprite.setTexture(Constants::instance.textureProjectile);
    sprite.setScale(0.5f, 0.5f);
}

void Bomb::setOrigin()
{
    sf::Vector2f size{sprite.getTexture() -> getSize()};
    sprite.setOrigin(size.x/2, size.y/2);
}

void Bomb::setRadius()
{
    sf::Vector2f size{sprite.getTexture() -> getSize()};
    radius = (size.x + size.y) / 4;
}

