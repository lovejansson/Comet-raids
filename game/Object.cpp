//
// Created by love643 on 2019-12-14.
//

#include <SFML/Graphics.hpp>

#include "Object.h"

//////////////////
// Constructor //
/////////////////

Object::Object(sf::Vector2f const& position)
: sprite{}, alive{true}
{
    sprite.setPosition(position);
}

/////////////////////////////
// Public member functions //
////////////////////////////

bool Object::isAlive() const
{
    return alive;
}

sf::Sprite Object::getSprite() const
{
    return sprite;
}

void Object::draw(sf::RenderWindow & drawTo) const
{
    drawTo.draw(sprite);
}

