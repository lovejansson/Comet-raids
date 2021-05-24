//
// Created by chasi127 on 2019-12-08.
//

#ifndef COMET_RAID_ICEBLOCK_H
#define COMET_RAID_ICEBLOCK_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "DynamicObject.h"
#include "GameState.h"

using dynamicObjPtr = std::shared_ptr<DynamicObject>;

class IceBlock : public DynamicObject{
public:
    IceBlock(sf::Vector2f const& position);
    IceBlock(sf::Vector2f const& position, float const mass,
             sf::Vector2f const& speedDir);

    /**
     * Updates rotation of ice block and calls parent class update function.
     * @param view Variable needed in sibling class Ship update function.
     * @param world Variable needed in sibling class Ship update function.
     */
    void update(sf::View & view, GameState& world) override;

    /**
     * Updates hp variable after collision and checks if ice block is to be killed.
     * @param world Variable passed to subsequent function.
     */
    void collisionUpdate(GameState& world) override;

    /**
     * Getter for age of ice block.
     * @return int age and number of seconds passed since constructed.
     */
    int getAge() const;

private:
    /* Variables */
    /**
     * sf::Clock used to keep track of the IceBlocks age.
     */
    sf::Clock clock;

    /**
     * int representing size of IceBlock.
     */
    int blockSize;

    /**
     * int representing hp.
     */
    int hp;

    /**
     * int representing age.
     */
    int age;

    /* Functions */
    /**
     * Initializes sf::Texture.
     */
    void initializeTexture();

    /**
    * Sets origin of IceBlock.
    */
    void setRadius();

    /**
     * Sets orientation of IceBlock.
     */
    void setOrientation();

    /**
    * Sets origin of IceBlock.
    */
    void setOrigin();

    /**
     * Handles split between IceBlocks when they have collided i.e. creates new IceBlocks
     * based on old IceBlocks values of mass, position, direction and speed.
     * @param world Variable used to access addObject in GameState to add the newly created IceBlocks.
     */
    void splitIceBlock(GameState& world);
};

#endif //COMET_RAID_ICEBLOCK_H
