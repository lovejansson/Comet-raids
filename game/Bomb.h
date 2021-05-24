//
// Created by love643 on 2019-12-11.
//

#ifndef COMET_RAID_BOMB_H
#define COMET_RAID_BOMB_H

#include <SFML/Graphics.hpp>

#include "DynamicObject.h"
#include "GameState.h"


class Bomb : public DynamicObject{
public:
    Bomb(sf::Vector2f const& position,
         sf::Vector2f const& direction, float const speed);

    /**
     * Updates safe status of Bomb and calls parent class update function.
     * @param view Variable needed in sibling class Ship update function.
     * @param world Variable needed in sibling class Ship update function.
     */
    void update(sf::View & view, GameState & world) override;

    /**
     * Creates new explosion if the Bomb is colliding while safe == false.
     * @param world Variable used to access addObject in GameState
     */
    void collisionUpdate(GameState& world) override;
private:
    /* Variables */
    /**
     * sf::Clock used to keep track of number of seconds since Bomb was constructed.
     */
    sf::Clock clock;

    /**
     * int representing timerSec, i.e., the number of seconds until safe == false.
     */
    int timerSec;

    /**
     * bool representing if Bomb is safe or not, i.e. if it can explode or not.
     */
    bool safe;

    /* Functions */
    /**
     * Initializes sf::Text variables.
     */
    void initializeTexture();

    /**
     * Sets origin of Bomb.
     */
    void setOrigin();

    /**
    * Sets radius of Bomb.
    */
    void setRadius();
};

#endif //COMET_RAID_BOMB_H
