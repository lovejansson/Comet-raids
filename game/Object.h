//
// Created by love643 on 2019-12-14.
//

#ifndef COMET_RAID_OBJECT_H
#define COMET_RAID_OBJECT_H

#include <SFML/Graphics.hpp>

class Object {
public:
    Object(sf::Vector2f const& position);
    virtual ~Object() = default;

    /**
     * Getter for alive variable. 
     * @return bool true if the Object is still alive else false.
     */
    bool isAlive() const;

    /**
     * Getter for sf::Sprite sprite. 
     * @return sf::Sprite 
     */
    sf::Sprite getSprite() const;

    /**
     * Draws the sprite of Object to game window. 
     * @param drawTo window to render to. 
     */
    void draw(sf::RenderWindow & drawTo) const;

protected:

    /**
     * sf::Sprite representing object sprite. 
     */
    sf::Sprite sprite;

    /**
     * bool to keep track of the life status of object. 
     */
    bool alive;
};

#endif //COMET_RAID_OBJECT_H
