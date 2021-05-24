//
// Created by chasi127 on 2019-12-16.
//

#include <SFML/Graphics.hpp>

#include "Projectile.h"
#include "Constants.h"
#include "GameState.h"

///////////////////
// Constructor ///
//////////////////

Projectile::Projectile(sf::Vector2f const& position, sf::Vector2f const& direction, float const speed)
: DynamicObject{position, 50, direction, speed, 90}
{
    initializeTexture();
    setOrigin();
    setRadius();
}

/////////////////////////////
// Public member functions //
/////////////////////////////

void Projectile::collisionUpdate(GameState& world)
{
    alive = false;
}

//////////////////////////////
// Private member functions //
/////////////////////////////

void Projectile::initializeTexture()
{
    sprite.setTexture(Constants::instance.textureProjectile);
    sprite.setScale(0.1f, 0.1f);
}

void Projectile::setOrigin()
{
    sf::Vector2f size{sprite.getTexture() -> getSize()};
    sprite.setOrigin(size.x/2, size.y/2);
}

void Projectile::setRadius()
{
    sf::Vector2f size{sprite.getTexture() -> getSize()};
    radius = (size.x + size.y) / 4;
}
