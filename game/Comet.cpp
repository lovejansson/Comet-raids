//
// Created by chasi127 on 2019-12-10.
//

#include "Comet.h"
#include "Constants.h"

/////////////////
// Constructor //
/////////////////

Comet::Comet(int const currentLevel)
: StaticObject{{0, 0}}
{
    sprite.setTexture(Constants::instance.getLevelTexture(currentLevel));
}
