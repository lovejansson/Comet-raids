//
// Created by chasi127 on 2019-12-15.
//

#ifndef COMET_RAID_CONSTANTS_H
#define COMET_RAID_CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <vector>

/**
 * Constants holds all game constants that are not going to change mid game and needs to stay in the memory until
 * the game ends.
 */
class Constants {
public:
        Constants();
        /*TEXTURES*/
        /*Animations*/
        /**
         * Texture for the Explosion Animation.
         */
        sf::Texture textureExplosion;
        /*static textures*/

        /**
         * Texture for the IceBlock Class.
         */
        sf::Texture textureIceBlock;

        /**
         * Texture for the Ship Class.
         */
        sf::Texture textureShip;

        /**
         * Texture for the Bomb Class.
         */
        sf::Texture textureBomb;

        /**
         * Texture for the Projectile Class.
         */
        sf::Texture textureProjectile;

         /**
         * Texture for the BombSite Class.
         */
        sf::Texture textureBombSite;

         /*Fonts*/
         /**
         * The sf::Font for all game texts.
         */
        sf::Font font;

         /*Mist*/
         /**
         * The tickRate for the game in ticks per second.
         */
        long tickRate;

        /*functions */
        /**
         * Returns a sf::Texture reference to the texture indicated by the level variable.
         * @param level The level.
         * @return sf::Texture reference.
         */
        sf::Texture& getLevelTexture(int level);

        /**
         * Returns the Bombsite coordinates in a vector for the indicated level.
         * @param level The level.
         * @return std::vector<sf::Vector2f> reference.
         */
        std::vector<sf::Vector2f>& getLevelBombSites(int level);

        /**
         * Returns the player start coordinates in a vector for the indicated level.
         * @param level The level.
         * @return std::vector<sf::Vector2f> reference.
         */
        std::vector<sf::Vector2f>& getPlayerLocation(int level);

        /**
         * Returns the endTimer duration for the indicated level.
         * @param level The level.
         * @return int
         */
        int getLevelTimer(int level) const;

        /**
         * Returns the total amount of levels in the game.
         * @return int Number of levels.
         */
        int getNumberOfLevels() const;

        /**
        * Declares the instance of the Constants class.
        */
        static Constants instance;
private:
    /* Variables */
    /*Level Textures*/
    /**
    * std::vector containing all the level textures.
    */
    std::vector<sf::Texture> levelTextures;

    /*Coordinates*/
    /**
    * std::vector with a vector for each level containing the BombSite coordinates.
    */
    std::vector<std::vector<sf::Vector2f>> bombSites;
    /**
    * std::vector with a vector for each level containing the player start locations coordinates.
    */
    std::vector<std::vector<sf::Vector2f>> playerLocations;

    /*Timers*/
    /**
    * std::vector with a vector for each level containing the endTimer durations.
    */
    std::vector<int> levelTimers;

    /* Functions */
    /**
     * Loads level information from text file.
     */
    void loadLevels();

    /**
     * Loads a png file into the levelTextures vector.
     * Used in the loadLevels method.
     * @param address The address to the png file.
     */
    void loadTexture(std::string const& address);

    /**
     * Initializes Object textures.
     */
     void initializeTextures();
};

#endif //COMET_RAID_CONSTANTS_H
