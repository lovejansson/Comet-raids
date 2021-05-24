//
// Created by chasi127 on 2019-12-03.
//

#ifndef COMET_RAID_SHIP_H
#define COMET_RAID_SHIP_H

#include <SFML/Graphics.hpp>

#include "DynamicObject.h"
#include "GameState.h"

class Ship : public DynamicObject{
public:
    Ship(sf::Vector2f const& position);

    /**
     * Updates ship i.e., calling functions for updating texts, detecting pressed down keys and do
     * necessarily changes accordingly and finally calling other functions to update position of Ship
     * and sf::View.
     * @param view Variable passed to subsequent functions.
     * @param world Variable passed to subsequent functions and to access addObject in GameState.
     */
    void update(sf::View & view, GameState& world) override;

    /**
     * Updates variable hp and shieldHp after collision and checks if ship is to be killed.
     * @param world Variable used to access setShipDied function in GameState.
     */
    void collisionUpdate(GameState & world) override;

    /**
     * Renders sf::Text variables to game window.
     * @param drawTo the window to draw to.
     */
    void drawText(sf::RenderWindow & drawTo) const;

private:
    /* Variables */
    /**
     * float representing hp.
     */
    float hp;

    /**
     * float representing maximum hp value.
     */
    float maxHp;

    /**
     * float representing shieldHp.
     */
    float shieldHp;

    /**
     * float representing maximum shieldHp
     */
    float maxShieldHp;

    /**
     * int representing number of bombs.
     */
    int bombs;

    /**
     * float representing acceleration.
     */
    float shipAcceleration;

    /**
     * float representing rotation speed.
     */
    float shipRotationSpeed;

    /**
     * sf::Text of current hp level.
     */
    sf::Text hpCountdown;

    /**
     * sf::Text of current shieldHp level.
     */
    sf::Text shieldHpCountdown;

    /**
     * sf::Text of current number of bombs left.
     */
    sf::Text bombsLeft;

    /* Functions */
    /**
     * Initializes sf::Texture.
     */
    void initializeText();

    /**
     * Initializes sf::Text variables.
     */
    void initializeTexture();

    /**
     * Sets radius of Ship.
     */
    void setRadius();

    /**
     * Sets origin of Ship.
     */
    void setOrigin();

    /**
     * Updating position of view according to ships position and proximity to edges of level.
     * This is to make sure that view stays within the confines of the level and has the same
     * center as the ships position.
     * @param view The view to update.
     * @param world Variable used to access functions in GameState.
     */
    void updateView(sf::View & view, GameState& world) const;

    /**
     * Updates content of sf::Text variables according to changes in variables hp and shieldHp.
     */
    void updateTextContent();

    /**
     * Updates positions of sf::Text variables according to position of sf::View.
     * @param view The view to adjust positions to.
     * @param world Variable used to adjust sf::Text variable in GameState.
     */
    void updateTextPositions(sf::View & view, GameState& world);

    /**
     * Updates the speed and direction of the Ship.
     * @param world GameState reference to access the keys map.
    */
    void updateSpeedDirection(GameState& world);

    /**
     * Updates the rotation of the Ship and View.
     * @param view The view to be updated.
     * @param world GameState reference to access the keys map.
     */
    void updateRotation(sf::View & view, GameState& world);

    /**
     * Fires off the ship weapons by updating the GameState with Bomb and Projectile instances.
     * @param world GameState reference to access the keys map and the addObject method.
     */
    void updateWeapons(GameState& world);

    /**
     * Regenerates the shield of the ship.
     */
    void regenerateShield();
};

#endif //COMET_RAID_SHIP_H
