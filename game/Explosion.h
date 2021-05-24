//
// Created by chasi127 on 2019-12-12.
//

#ifndef COMET_RAID_EXPLOSION_H
#define COMET_RAID_EXPLOSION_H

#include <SFML/Graphics.hpp>

#include "StaticObject.h"

class Explosion : public StaticObject{
public:
    Explosion(sf::Vector2f const& position);

    /**
     * Updates the Explosion animation
     */
    void update();
private:

    /**
     * A sf::Clock to keep track when to update the animation.
     */
    sf::Clock clock;
};

#endif //COMET_RAID_EXPLOSION_H
