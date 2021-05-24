//
// Created by chasi127 on 2019-12-03.
//

#ifndef COMET_RAID_DYNAMICOBJECT_H
#define COMET_RAID_DYNAMICOBJECT_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "Object.h"
#include "GameState.h"
#include "StaticObject.h"

class DynamicObject;
class GameState;

using dynamicObjPtr = std::shared_ptr<DynamicObject>;
using staticObjPtr = std::shared_ptr<StaticObject>;

class DynamicObject : public Object{
public:
    DynamicObject(sf::Vector2f const& position, float mass,
            sf::Vector2f const & direction, float speed, float orientDegrees);
    virtual ~DynamicObject() = default;

    /**
     * Updates position of dynamic object.
     * @param view Variable used in subclasses update functions (overrides this function).
     * @param world Variable used in subclasses update functions (overrides this function).
     */
    virtual void update(sf::View & view, GameState & world);

    /**
     * Pure virtual function. Implemented in subclasses to update variables after collision.
     * @param world Variable used in subclasses collisionUpdate (overrides this function).
     * @param view Variable used in subclasses collisionUpdate (overrides this function).
     */
    virtual void collisionUpdate(GameState & world) = 0;

    /**
     * Calculates position of DynamicObject after elastic collision with DynamicObject.
     * @param other DynamicObject that has collided with current DynamicObject.
     * @param view Variable passed down to subsequent function and collisionUpdate of subclasses.
     * @param world Variable passed down to subsequent function and collisionUpdate of subclasses.
     */
    void elasticCollision(dynamicObjPtr const& other, sf::View & view, GameState & world);

    /**
     * Calculates position of DynamicObject after elastic collision with StaticObject.
     * @param other StaticObject that has collided with current DynamicObject.
     * @param view Variable passed down to subsequent function and collisionUpdate of subclasses.
     * @param world Variable passed down to subsequent function and collisionUpdate of subclasses.
     */
    void elasticCollision(staticObjPtr const& other, sf::View & view, GameState & world);

    /**
     * Handles inelastic collision between two DynamicObjects i.e. creates new DynamicObject
     * with new speed, direction and mass.
     * @param other DynamicObject that has collided with current DynamicObject.
     * @return DynamicObjPtr shared_pointer<DynamicObject> to the created DynamicObject.
     */
    dynamicObjPtr inelasticCollision(dynamicObjPtr & other);

    /**
     * Getter for variable speed.
     * @return float speed.
     */
    float getSpeed() const;

    /**
     * Setter for variable alive.
     * @param status which status true or false to set the alive variable to.
     */
    void setAliveStatus(bool const status);

protected:
    /* Variables */
    /**
     * float representing mass.
     */
    float mass;

    /**
     * Normalized vector representing direction.
     */
    sf::Vector2f direction;

    /**
     * Normalized vector representing orientation.
     */
    sf::Vector2f orientation;

    /**
     * float representing speed.
     */
    float speed;

    /**
     * float representing radius.
     */
    float radius;

    /* Functions */
    /**
     * Calculates new vector when old vector is rotated.
     * @param orientation old vector to rotate.
     * @param degrees How many degrees to rotate old vector.
     * @return sf::vector2f new rotated vector.
     */
    static sf::Vector2f rotateVector(sf::Vector2f const& orientation, float const degrees);

    /**
     * Normalizes velocity vector and updates speed and direction.
     * @param SpeedDirection velocity to normalize.
     */
    void normalizeSpeedDirection(sf::Vector2f const& SpeedDirection);

    /**
     * Creates normalized direction vector.
     * @param vector velocity vector to normalize.
     * @return sf::vector2f normalized vector.
     */
    sf::Vector2f calculateNormalizedVector(sf::Vector2f const& vector) const;

private:

    /**
     * Calculates average normal vector between current DynamicObject position and the colliding
     * pixels between current DynamicObject and other Object.
     * @param other Sprite that has collided with current DynamicObject.
     * @return sf::Vector2f average normal vector.
     */
    sf::Vector2f getAverageCollidingPixel(sf::Sprite const& other) const;

    /**
     * Adjust position of DynamicObject and view after a collision.
     * @param view the view to adjust.
     * @param averageCollisionNormal vector needed for calculation of average distance to colliding pixels.
     */
    void adjustPosition(sf::View & view, sf::Vector2f const& averageCollisionNormal);

    /**
     * Calculates length of vector.
     * @param vector to calculate length from.
     * @return float length.
     */
    float calculateVector2fLength(sf::Vector2f const& vector) const;
};

#endif //COMET_RAID_DYNAMICOBJECT_H
