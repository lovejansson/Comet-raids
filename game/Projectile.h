//
// Created by chasi127 on 2019-12-16.
//

#ifndef COMET_RAID_PROJECTILE_H
#define COMET_RAID_PROJECTILE_H

#include <SFML/Graphics.hpp>

#include "DynamicObject.h"
#include "GameState.h"

class Projectile : public DynamicObject {

public:
    Projectile(sf::Vector2f const& position,
    sf::Vector2f const& direction, float const speed);

    /**
     * Sets alive to false when the Projectile collides.
     * @param world reference the the GameState.
     * @param view sf::View
     */
    void collisionUpdate(GameState& world) override;
private:

    /**
     * Initializes the textures for the Projectile
     */
    void initializeTexture();

    /**
     * sets the origin the the Projectiles Sprite.
     */
    void setOrigin();

    /**
     *Calculates and sets the radius variable of the Projectile
     */
    void setRadius();
};

#endif //COMET_RAID_PROJECTILE_H
