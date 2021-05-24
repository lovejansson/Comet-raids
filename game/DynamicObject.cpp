//
// Created by chasi127 on 2019-12-03.
//

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <vector>

#include "DynamicObject.h"
#include "GameState.h"
#include "Collision.h"
#include "Constants.h"
#include "IceBlock.h"
#include "Bomb.h"
#include "Comet.h"

using dynamicObjPtr = std::shared_ptr<DynamicObject>;
using staticObjPtr = std::shared_ptr<StaticObject>;

///////////////////
// Constructor ///
//////////////////

DynamicObject::DynamicObject(sf::Vector2f const& position, float const mass,
               sf::Vector2f const& direction, float const speed, float const orientDegrees)
: Object{position}, mass{mass}, direction{direction}, orientation{}, speed{speed}, radius{}
{
    sprite.setRotation (orientDegrees);
    orientation = rotateVector(sf::Vector2f{0,-1}, orientDegrees);
}

/////////////////////////////
// Public member functions //
/////////////////////////////

void DynamicObject::update(sf::View & view, GameState& world)
{
    /* Prevents objects to go through walls */
    if(speed >= radius * float(Constants::instance.tickRate) * 2)
    {
        speed = radius * float(Constants::instance.tickRate - 1) * 2;
    }

    /* Updates position of object */
    sf::Vector2f change{direction * speed / float(Constants::instance.tickRate*2)};
    sprite.move(change);
}

/*TODO Förbättra kollisioner genom att hantera fall där objekt har mer än sin radie i
 * ett annat objekt */

/* Elastic collision dynamic object versus dynamic object */
void DynamicObject::elasticCollision(dynamicObjPtr const& other, sf::View & view, GameState & world)
{
    if(alive && other->isAlive())
    {
        /* The position of both objects */
        sf::Vector2f position1{sprite.getPosition()};
        sf::Vector2f position2{other->sprite.getPosition()};

        /* Current normalized normal vector and tangent vector for current object */
        sf::Vector2f normal{position2 - position1};
        normal = calculateNormalizedVector(normal);
        sf::Vector2f tangent{-normal.y, normal.x};

        /* Velocity vector for both objects */
        sf::Vector2f VelocityOne{direction * speed};;
        sf::Vector2f VelocityTwo{other->direction * other->speed};

        /* Normal part of velocity vectors before collision for both objects */
        float VelocityN1{normal.x * VelocityOne.x + normal.y * VelocityOne.y};
        float VelocityN2{normal.x * VelocityTwo.x + normal.y * VelocityTwo.y};

        /* Tangent part of velocity vector for current object(same before and after collision) */
        float VelocityTangent{tangent.x * VelocityOne.x + tangent.y + VelocityOne.y};

        /* New speed of normal part after collision for current object */
        float newSpeed{((mass - other->mass) * VelocityN1 + 2 * other->mass * VelocityN2)
                       / (mass + other->mass)};

        /* New normal vector and tangent vector for current object */
        sf::Vector2f newVelocityNormal{newSpeed * normal};
        sf::Vector2f newVelocityTangent{VelocityTangent * tangent};

        /* Ǹew normalized velocity for current object */
        sf::Vector2f newSpeedDirection{newVelocityNormal + newVelocityTangent};

        /* Average difference vector between the position of current object and all colliding
         * points */
        sf::Vector2f pointsOfCollisionNormal{getAverageCollidingPixel(other->sprite)};

        /* Adjusting current objects position for the collision */
        adjustPosition(view, pointsOfCollisionNormal);

        /* Changing speed and direction for current object */
        normalizeSpeedDirection(newSpeedDirection);
        speed *= 0.9;

        /* Update variables of current object */
        if(typeid(*other) != typeid(Bomb)) {
            collisionUpdate(world);
        }
    }
}

void DynamicObject::elasticCollision(staticObjPtr const& other, sf::View & view, GameState & world)
{
    if(alive && other->isAlive())
    {
        /* Average difference vector between the position of current object and all colliding
         * points */
        sf::Vector2f pointsOfCollisionNorm{getAverageCollidingPixel(other->getSprite())};

        /* Current normalized normal vector and tangent vector for current object */
        sf::Vector2f normal{};
        normal = calculateNormalizedVector(pointsOfCollisionNorm);
        sf::Vector2f tangent{-normal.y, normal.x};

        /* Velocity for current object*/
        sf::Vector2f Velocity{direction * speed};

        /* Normal part of speed before collision of current object */
        float VelocityNormal{normal.x * Velocity.x + normal.y * Velocity.y};

        /* Tangent part of speed of current object (same before and after collision */
        float VelocityTangent{tangent.x * Velocity.x + tangent.y + Velocity.y};

        /* New speed after collision */
        float newSpeed{-1 * VelocityNormal};

        /* New normal vector and tangent vector for current object */
        sf::Vector2f newVelocityNormal{newSpeed * normal};
        sf::Vector2f newVelocityTangent{VelocityTangent * tangent};

        /* New normalized velocity vector for current object */
        sf::Vector2f newSpeedDirection{newVelocityNormal + newVelocityTangent};

        /*  Adjusting current objects position for the collision */
        adjustPosition(view, pointsOfCollisionNorm);

        /* Changing speed and direction for current object */
        normalizeSpeedDirection(newSpeedDirection);
        speed *= 0.9;

        /* Update variables of current object */
        collisionUpdate(world);
    }
}

dynamicObjPtr DynamicObject::inelasticCollision(dynamicObjPtr & other)
{
    if(alive && other->isAlive())
    {
        /* Total momentum before collision */
        sf::Vector2f momentum1{mass * direction * speed};
        sf::Vector2f momentum2{other->mass * other->direction * other->speed};
        sf::Vector2f totalMomentum{momentum1 + momentum2};

        /* Normalized normal */
        sf::Vector2f normal{sprite.getPosition() - other->sprite.getPosition()};
        float distance = calculateVector2fLength(normal);
        normal = calculateNormalizedVector(normal);

        /* Adjusted normal in order to find exact position between objects */
        float adjustedNormalLength{distance - radius};
        sf::Vector2f newNormal = normal * adjustedNormalLength;
        sf::Vector2f newPosition{sprite.getPosition() - newNormal};

        float newMass{mass + other->mass};
        sf::Vector2f speedDir{totalMomentum / newMass};

        /* Creating new ice block */
        sf::Texture texture{};
        dynamicObjPtr newDynamicObject{};
        newDynamicObject = dynamicObjPtr{new IceBlock{newPosition,
                                                      newMass, speedDir}};
        /* Killing old objects */
        alive = false;
        other->setAliveStatus(false);
        return newDynamicObject;
    }
    return nullptr;
}

float DynamicObject::getSpeed() const
{
    return speed;
}

void DynamicObject::setAliveStatus(bool const status)
{
    alive = status;
}

////////////////////////////////
// Protected member functions //
///////////////////////////////

sf::Vector2f DynamicObject::rotateVector(sf::Vector2f const& orientation, float const degrees) 
{
    auto radians {float(degrees * (M_PI/180))};

    float cos{cosf(radians)};
    float sin{sinf(radians)};

    float oldX{orientation.x};
    float oldY{orientation.y};

    float x{oldX*cos-oldY*sin};
    float y{oldX*sin+oldY*cos};

    return sf::Vector2f {x, y};
}

void DynamicObject::normalizeSpeedDirection(sf::Vector2f const& SpeedDirection)
{
    speed = calculateVector2fLength(SpeedDirection);
    if (speed != 0) {
        direction = sf::Vector2f{SpeedDirection.x / speed, SpeedDirection.y / speed};
    }
    else {
        direction = sf::Vector2f{0, 0};
    }
}

sf::Vector2f DynamicObject::calculateNormalizedVector(sf::Vector2f const& vector) const
{
    float length = calculateVector2fLength(vector);
    if (length != 0)
        return sf::Vector2f{vector.x / length, vector.y / length};
    else
        return sf::Vector2f{0,0};
}

///////////////////////////////
// Private member functions //
/////////////////////////////

sf::Vector2f DynamicObject::getAverageCollidingPixel(sf::Sprite const& other) const
{
    sf::Vector2f averageCollisionNormal{};
    std::vector<sf::Vector2f> collidingPixels{Collision::getPixelsOverlap(sprite, other)};

    sf::Vector2f pos{sprite.getPosition()};

    for(auto point: collidingPixels)
    {
        sf::Vector2f tempVector{point - pos};
        averageCollisionNormal += calculateNormalizedVector(tempVector);
    }
    averageCollisionNormal = calculateNormalizedVector(averageCollisionNormal);

    return averageCollisionNormal;
}

void DynamicObject::adjustPosition(sf::View & view, sf::Vector2f const& averageCollisionNormal)
{
    float averagePixelDistance{};
    averagePixelDistance = calculateVector2fLength(averageCollisionNormal);

    sf::Vector2f dirCollNrm{direction - averageCollisionNormal};
    sprite.move(calculateNormalizedVector(dirCollNrm) *
    (radius + float(averagePixelDistance)) / float(Constants::instance.tickRate * 2));

    view.move(calculateNormalizedVector(dirCollNrm) *
    (radius + float(averagePixelDistance)) / float(Constants::instance.tickRate * 2));

}

float DynamicObject::calculateVector2fLength(sf::Vector2f const& vector) const
{
    return sqrt((vector.x * vector.x ) + (vector.y * vector.y));
}