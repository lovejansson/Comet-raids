//
// Created by chasi127 on 2019-12-03.
//

#include <SFML/Graphics.hpp>
#include <map>

#include "State.h"

/////////////////
// Constructor //
/////////////////

State::State(int const currentLevel)
: currentLevel{currentLevel}
{}

/////////////////////////////
// Public member functions //
/////////////////////////////

void State::onKeyPressed(sf::Keyboard::Key key)
{
    if(keys.find(key) != end(keys))
    {
        keys.insert_or_assign(key, true);
    }
}

void State::onKeyReleased(sf::Keyboard::Key key)
{
    if(keys.find(key) != end(keys))
    {
        keys.insert_or_assign(key, false);
    }
}

std::map<sf::Keyboard::Key, bool> const& State::getKeys() const
{
    return keys;
}