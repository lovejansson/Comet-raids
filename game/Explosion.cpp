//
// Created by chasi127 on 2019-12-12.
//

#include <SFML/Graphics.hpp>

#include "Explosion.h"
#include "Constants.h"

//////////////////
// Constructor //
/////////////////


Explosion::Explosion(sf::Vector2f const& position)
: StaticObject{position}, clock{}
{
    sprite.setTexture(Constants::instance.textureExplosion);
    sprite.setTextureRect({0, 0, 512, 512});
    sprite.setOrigin(sprite.getTextureRect().width/2, sprite.getTextureRect().height/2);
    sprite.setScale(0.5f, 0.5f );
}

/////////////////////////////
// Public member functions //
/////////////////////////////

void Explosion::update()
{
    if (clock.getElapsedTime().asMilliseconds() > 10.0f){
        if(sprite.getTextureRect().left == 512*7 && sprite.getTextureRect().top == 512*4)
        {
            alive = false;
        }
        else if (sprite.getTextureRect().left == 512*7) {

            sprite.setTextureRect({0, sprite.getTextureRect().top + 512, 512, 512});
        }
        else {
            sprite.setTextureRect({sprite.getTextureRect().left + 512, sprite.getTextureRect().top, 512, 512});

        }
        clock.restart();
    }
}
