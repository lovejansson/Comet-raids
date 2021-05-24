//
// Created by chasi127 on 2019-12-12.
//

#include <SFML/Graphics.hpp>

#include "BombSite.h"
#include "Constants.h"
#include "GameState.h"

/////////////////
// Constructor //
/////////////////

BombSite::BombSite(sf::Vector2f const& position)
: StaticObject{position}, bombPlaced{false}
{
    sprite.setTexture(Constants::instance.textureBombSite);
    sprite.setTextureRect({160, 0, 160, 159});
    sprite.setOrigin(sprite.getTextureRect().width/2, sprite.getTextureRect().height/2);
    sprite.setScale(0.5f, 0.5f);
}

/////////////////////////////
// Public member functions //
/////////////////////////////

void BombSite::collisionUpdate(GameState & world)
{
    if(!bombPlaced)
    {
        bombPlaced = true;
        world.addOneBombPlaced();
        sprite.setTextureRect({0, 0, 160, 159});
    }
}
