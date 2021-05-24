//
// Created by chasi127 on 2019-12-03.
//

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>

#include "Ship.h"
#include "DynamicObject.h"
#include "GameState.h"
#include "Bomb.h"
#include "Constants.h"
#include "Projectile.h"

using dynamicObjPtr = std::shared_ptr<DynamicObject>;

///////////////////
// Constructor ///
//////////////////

Ship::Ship(sf::Vector2f const& position)
: DynamicObject{position, 5000, {0, 0}, 0, 90}, hp{100}, maxHp{100},
          shieldHp{1000}, maxShieldHp{1000}, bombs{30}, hpCountdown{}, shieldHpCountdown{}, bombsLeft{},
          shipAcceleration{8}, shipRotationSpeed{2}
{
    initializeTexture();
    setRadius();
    setOrigin();
    initializeText();
}

/////////////////////////////
// Public member functions //
////////////////////////////

void Ship::update(sf::View & view, GameState& world)
{
    updateTextContent();
    updateTextPositions(view, world);

    updateSpeedDirection(world);
    updateRotation(view, world);
    updateWeapons(world);
    regenerateShield();

    DynamicObject::update(view, world);
    updateView(view, world);
}

void Ship::updateSpeedDirection(GameState& world)
{
    sf::Vector2f currentSpeedDirection{speed * direction};
    if(world.getKeys().at(sf::Keyboard::A))
    {
        currentSpeedDirection += rotateVector(orientation,-90) * shipAcceleration;
    }
    if(world.getKeys().at(sf::Keyboard::D))
    {
        currentSpeedDirection +=  rotateVector(orientation,90) * shipAcceleration;
    }
    if(world.getKeys().at(sf::Keyboard::W))
    {
        currentSpeedDirection += (orientation * shipAcceleration) ;
    }
    if(world.getKeys().at(sf::Keyboard::S))
    {
        currentSpeedDirection -= (orientation * shipAcceleration);
    }
    normalizeSpeedDirection(currentSpeedDirection);
}

void Ship::collisionUpdate(GameState& world)
{
    if(shieldHp <= 0)
    {
        hp -= 10;

    }
    else
    {
        shieldHp -= 50;
        if(shieldHp < 0)
        {
            shieldHp = 0;
        }
    }

    if(hp < 1)
    {
        alive = false;
        world.setShipDied();
    }
}

void Ship::drawText(sf::RenderWindow & drawTo) const
{
    drawTo.draw(shieldHpCountdown);
    drawTo.draw(hpCountdown);
    drawTo.draw(bombsLeft);
}

//////////////////////////////
// Private member functions //
//////////////////////////////

void Ship::initializeText()
{
    hpCountdown.setString("LIV: " + std::to_string(hp ));
    shieldHpCountdown.setString("ENERGI PANSAR: " + std::to_string(shieldHp));
    bombsLeft.setString("BOMBER: " + std::to_string(bombs));
    hpCountdown.setCharacterSize(10);
    shieldHpCountdown.setCharacterSize(10);
    bombsLeft.setCharacterSize(10);

    hpCountdown.setFont(Constants::instance.font);
    shieldHpCountdown.setFont(Constants::instance.font);
    bombsLeft.setFont(Constants::instance.font);
    hpCountdown.setRotation(90);
    shieldHpCountdown.setRotation(90);
    bombsLeft.setRotation(90);
}

void Ship::initializeTexture()
{
    sprite.setTexture(Constants::instance.textureShip);
    sprite.setScale(0.5f, 0.5f);
}

void Ship::setRadius()
{
    sf::Vector2f size{sprite.getTexture() -> getSize()};
    radius = (size.x + size.y) / 4;
}

void Ship::setOrigin()
{
    sf::Vector2f size{sprite.getTexture() -> getSize()};
    sprite.setOrigin(size.x/2, size.y/2);
}

void Ship::updateView(sf::View & view, GameState& world) const
{
    /* Old position of view */
    sf::Vector2f oldCenter{};
    oldCenter = view.getCenter();

    /* Updates position of view */
    sf::Vector2f change{direction * speed / float(Constants::instance.tickRate * 2)};
    view.move(change);

    /* Maximum values of comets width and height */
    std::pair<float, float> cometSize{};
    cometSize = world.getCometSize();
    float cometHeight{};
    cometHeight = cometSize.second;
    float cometWidth{};
    cometWidth = cometSize.first;

    /* Gets information about the center and size of view */
    sf::Vector2f viewCenter{};
    viewCenter = view.getCenter();
    sf::Vector2f viewSize{};
    viewSize = view.getSize();

    /* New Center */
    sf::Vector2f newCenter{0, 0};

    /* Adjust view according to window size */
    if(viewCenter.x + viewSize.x / 2 >= cometWidth)
    {
        newCenter.x = cometWidth - viewSize.x / 2;
    }
    else if(viewCenter.x - viewSize.x / 2 <= 0)
    {
        newCenter.x = 0 + viewSize.x / 2;
    }
    else if(viewCenter.y + viewSize.y / 2 >= cometHeight)
    {
        newCenter.y = cometHeight - viewSize.y / 2;
    }
    else if(viewCenter.y - viewSize.y / 2 <= 0)
    {
        newCenter.y = 0 + viewSize.y / 2;
    }

    /* Adjust view according to if ship moves along edges of comet */
    if(sprite.getPosition().x  < viewSize.x / 2)
    {
        newCenter.x = oldCenter.x;
    }
    else if(sprite.getPosition().x > cometWidth - viewSize.x / 2)
    {
        newCenter.x = oldCenter.x;
    }
    else if(sprite.getPosition().y < viewSize.y / 2)
    {
        newCenter.y = oldCenter.y;
    }
    else if(sprite.getPosition().y > cometHeight - viewSize.y / 2)
    {
        newCenter.y = oldCenter.y;
    }

    /* Updates center of view */
    if(newCenter.x != 0)
    {
        viewCenter.x = newCenter.x;
    }
    if(newCenter.y != 0)
    {
        viewCenter.y = newCenter.y;
    }

    view.setCenter(viewCenter);
}

void Ship::updateTextContent()
{
    hpCountdown.setString("LIV: " + std::to_string(int(hp)));
    shieldHpCountdown.setString("ENERGI PANSAR: " + std::to_string(int(shieldHp)));
}

void Ship::updateTextPositions(sf::View & view, GameState& world)
{
    sf::Vector2f viewCenter{};
    viewCenter = view.getCenter();

    /* New positions */
    sf::Vector2f timerPos{viewCenter + orientation * 250.f};
    sf::Vector2f hpPos{timerPos + rotateVector(orientation, -90) * 365.f};
    sf::Vector2f shieldHpPos{hpPos + orientation * -15.f};
    sf::Vector2f bombsLeftPos{shieldHpPos + orientation * -15.f};

    /* Updating positions */
    world.getEndTimerText().setPosition(timerPos);
    world.getEndTimerText().setOrigin(world.getEndTimerText().getLocalBounds().width/2,
                              world.getEndTimerText().getLocalBounds().height/2);
    hpCountdown.setPosition(hpPos);
    shieldHpCountdown.setPosition(shieldHpPos);
    bombsLeft.setPosition(bombsLeftPos);

    /* Updating rotation according to view */
    hpCountdown.setRotation(view.getRotation());
    shieldHpCountdown.setRotation(view.getRotation());
    bombsLeft.setRotation(view.getRotation());
    world.getEndTimerText().setRotation(view.getRotation());
}

void Ship::updateRotation(sf::View & view, GameState& world)
{
    if(world.getKeys().at(sf::Keyboard::Q))
    {
        sprite.rotate(-shipRotationSpeed);
        orientation = rotateVector(orientation,-shipRotationSpeed);
        view.rotate(-shipRotationSpeed);
    }
    if(world.getKeys().at(sf::Keyboard::E))
    {
        sprite.rotate(shipRotationSpeed);
        orientation = rotateVector(orientation,shipRotationSpeed);
        view.rotate(shipRotationSpeed);
    }
}

void Ship::updateWeapons(GameState &world)
{
    if(world.getKeys().at(sf::Keyboard::B))
    {
        if(bombs > 0)
        {
            dynamicObjPtr temp{};
            temp = dynamicObjPtr{new Bomb{sprite.getPosition() - orientation * 50.f, direction, speed}};
            world.addObject(temp);
            bombs -= 1;
            bombsLeft.setString("BOMBER: " + std::to_string(bombs));
        }
    }
    if(world.getKeys().at(sf::Keyboard::Space))
    {
        dynamicObjPtr temp{};
        temp = dynamicObjPtr{new Projectile{sprite.getPosition() + orientation * 45.f, orientation, 300}};
        world.addObject(temp);
    }
}

void Ship::regenerateShield()
{
    if(shieldHp < maxShieldHp && shieldHp > 1)
    {
        shieldHp += 0.01;
    }
}